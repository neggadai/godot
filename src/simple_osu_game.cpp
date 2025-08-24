#include "simple_osu_game.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void SimpleOsuGame::_bind_methods() {
    // Bind methods for Godot
}

SimpleOsuGame::SimpleOsuGame() {
    game_active = false;
    score = 0;
    combo = 0;
    game_time = 0.0f;
    
    background = nullptr;
    title_label = nullptr;
    score_label = nullptr;
    combo_label = nullptr;
    instructions_label = nullptr;
    
    active_circle_count = 0;
    next_spawn_time = 3.0f; // Start spawning after 3 seconds
    spawn_interval = 1.5f;  // Spawn every 1.5 seconds
}

SimpleOsuGame::~SimpleOsuGame() {
    // Cleanup
}

void SimpleOsuGame::_ready() {
    UtilityFunctions::print("Game initialized!");
    
    // Create dark background
    background = memnew(ColorRect);
    background->set_name("Background");
    background->set_size(Vector2(1280, 720));
    background->set_position(Vector2(0, 0));
    background->set_color(Color(0.05f, 0.05f, 0.15f, 1.0f));
    add_child(background);
    
    // Title
    title_label = memnew(Label);
    title_label->set_name("TitleLabel");
    title_label->set_position(Vector2(500, 100));
    title_label->set_text("OSU");
    title_label->set_modulate(Color(1, 0.8f, 1, 1));
    add_child(title_label);
    
    // Score display (top right like Osu)
    score_label = memnew(Label);
    score_label->set_name("ScoreLabel");
    score_label->set_position(Vector2(1000, 50));
    score_label->set_text("000000000");
    score_label->set_modulate(Color(1, 1, 1, 0.9f));
    add_child(score_label);
    
    // Combo display (bottom left like Osu)
    combo_label = memnew(Label);
    combo_label->set_name("ComboLabel");
    combo_label->set_position(Vector2(100, 600));
    combo_label->set_text("");
    combo_label->set_modulate(Color(1, 1, 1, 1));
    add_child(combo_label);
    
    // Instructions
    instructions_label = memnew(Label);
    instructions_label->set_name("InstructionsLabel");
    instructions_label->set_position(Vector2(400, 300));
    instructions_label->set_text("Click the circles!\nPress SPACE to start\nUse mouse to click circles");
    instructions_label->set_modulate(Color(1, 1, 1, 0.8f));
    add_child(instructions_label);
    
    UtilityFunctions::print("Simple Osu game ready!");
}

void SimpleOsuGame::_process(double delta) {
    game_time += delta;
    
    // Simple input handling using Input singleton
    Input* input = Input::get_singleton();
    
    // Check for space to start game
    if (input->is_action_just_pressed("ui_accept")) {
        if (!game_active) {
            start_game();
        }
    }
    
    // Check for click (mouse buttons or keyboard)
    if (input->is_action_just_pressed("ui_accept") || 
        input->is_action_just_pressed("ui_select") ||
        input->is_mouse_button_pressed(MOUSE_BUTTON_LEFT) ||
        input->is_mouse_button_pressed(MOUSE_BUTTON_RIGHT)) {
        if (game_active) {
            // Get actual mouse position
            Vector2 mouse_pos = get_viewport()->get_mouse_position();
            check_circle_hit(mouse_pos);
        }
    }
    
    if (game_active) {
        update_circles(delta);
        
        // Spawn new circles
        if (game_time >= next_spawn_time) {
            spawn_circle();
            next_spawn_time = game_time + spawn_interval;
        }
        
        update_ui();
    }
}

void SimpleOsuGame::start_game() {
    UtilityFunctions::print("Starting Osu game!");
    game_active = true;
    score = 0;
    combo = 0;
    game_time = 0.0f;
    next_spawn_time = 2.0f;
    
    // Clear any existing circles
    for (int i = 0; i < MAX_CIRCLES; i++) {
        if (circles[i].visual) {
            circles[i].visual->queue_free();
            circles[i].visual = nullptr;
        }
        circles[i].is_active = false;
    }
    active_circle_count = 0;
    
    // Hide instructions
    if (instructions_label) {
        instructions_label->set_visible(false);
    }
}

void SimpleOsuGame::spawn_circle() {
    // Find an inactive circle slot
    for (int i = 0; i < MAX_CIRCLES; i++) {
        if (!circles[i].is_active) {
            // Generate random position
            Vector2 pos = Vector2(
                150 + (float)(rand() % 980),  // X: 150-1130
                150 + (float)(rand() % 420)   // Y: 150-570
            );
            
            circles[i].position = pos;
            circles[i].spawn_time = game_time;
            circles[i].hit_time = game_time + 2.0f; // 2 seconds to hit
            circles[i].is_active = true;
            circles[i].is_hit = false;
            
            // Create visual
            circles[i].visual = create_circle(pos, Color(1, 0.3f, 0.1f, 1), 64);
            
            active_circle_count++;
            
            UtilityFunctions::print("Spawned circle at: ", pos);
            break;
        }
    }
}

void SimpleOsuGame::update_circles(float delta_time) {
    for (int i = 0; i < MAX_CIRCLES; i++) {
        if (circles[i].is_active && !circles[i].is_hit) {
            float time_left = circles[i].hit_time - game_time;
            
            if (time_left <= 0) {
                // Circle expired - miss
                if (circles[i].visual) {
                    circles[i].visual->queue_free();
                    circles[i].visual = nullptr;
                }
                circles[i].is_active = false;
                active_circle_count--;
                combo = 0; // Reset combo on miss
                UtilityFunctions::print("Missed circle - combo reset");
            } else {
                // Update approach circle effect (simple scaling)
                if (circles[i].visual) {
                    float progress = 1.0f - (time_left / 2.0f);
                    float scale = 2.0f - progress; // Shrink from 2x to 1x
                    circles[i].visual->set_scale(Vector2(scale, scale));
                    
                    // Change color as it gets closer to hit time
                    if (time_left < 0.5f) {
                        circles[i].visual->set_color(Color(1, 0.7f, 0.1f, 1)); // Orange when close
                    }
                }
            }
        }
    }
}

void SimpleOsuGame::check_circle_hit(Vector2 click_pos) {
    // Debug: Show click position
    UtilityFunctions::print("Click at: (", click_pos.x, ", ", click_pos.y, ")");
    
    for (int i = 0; i < MAX_CIRCLES; i++) {
        if (circles[i].is_active && !circles[i].is_hit) {
            // Circle center (account for visual offset)
            Vector2 circle_center = circles[i].position + Vector2(50, 50);
            float distance = click_pos.distance_to(circle_center);
            
            // Debug: Show circle info
            UtilityFunctions::print("Circle ", i, " at: (", circle_center.x, ", ", circle_center.y, ") distance: ", distance);
            
            if (distance <= 75.0f) { // Larger hit radius for easier clicking
                // Hit!
                circles[i].is_hit = true;
                
                if (circles[i].visual) {
                    circles[i].visual->set_color(Color(1, 1, 1, 1)); // Flash white
                    circles[i].visual->queue_free();
                    circles[i].visual = nullptr;
                }
                
                circles[i].is_active = false;
                active_circle_count--;
                
                // Score calculation (Osu-style)
                combo++;
                int base_score = 300; // Perfect hit
                int multiplier = 1 + (combo / 25);
                score += base_score * multiplier;
                
                UtilityFunctions::print("Hit! Score: ", score, " Combo: ", combo);
                return; // Only hit one circle per click
            }
        }
    }
    UtilityFunctions::print("No hit!");
}

void SimpleOsuGame::update_ui() {
    if (score_label) {
        String score_str = String::num_int64(score);
        score_label->set_text(score_str.pad_zeros(9));
    }
    
    if (combo_label) {
        if (combo > 0) {
            combo_label->set_text(String::num_int64(combo) + "x");
        } else {
            combo_label->set_text("");
        }
    }
}

ColorRect* SimpleOsuGame::create_circle(Vector2 pos, Color color, float size) {
    ColorRect* circle = memnew(ColorRect);
    circle->set_size(Vector2(size, size));
    circle->set_position(pos - Vector2(size/2, size/2)); // Center on position
    circle->set_color(color);
    add_child(circle);
    return circle;
}
