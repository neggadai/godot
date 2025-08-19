#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Player::_bind_methods() {
    // Register virtual methods that Godot needs to call
}

Player::Player() {
    speed = 300.0f;
    sprite = nullptr;
    camera = nullptr;
}

Player::~Player() {
    // Cleanup if needed
}

void Player::_ready() {
    // Initialize player
    UtilityFunctions::print("Player ready! Speed: ", speed);
    
    // Create Sprite2D programmatically
    sprite = memnew(Sprite2D);
    sprite->set_name("Sprite2D");
    add_child(sprite);
    
    // Create white texture
    Ref<Image> image = Image::create(64, 64, false, Image::FORMAT_RGB8);
    image->fill(Color(1, 1, 1, 1)); // Fill with white
    
    Ref<ImageTexture> texture = ImageTexture::create_from_image(image);
    sprite->set_texture(texture);
    
    UtilityFunctions::print("Created white Sprite2D!");
    
    // Create Camera2D programmatically
    camera = memnew(Camera2D);
    camera->set_name("Camera2D");
    camera->set_enabled(true);
    add_child(camera);
    
    UtilityFunctions::print("Created Camera2D!");
    UtilityFunctions::print("Player visual setup complete - ready to move!");
}

void Player::_physics_process(double delta) {
    Input* input = Input::get_singleton();
    
    Vector2 input_direction = Vector2();
    
    // Get input direction
    if (input->is_action_pressed("ui_right")) {
        input_direction.x += 1;
    }
    if (input->is_action_pressed("ui_left")) {
        input_direction.x -= 1;
    }
    if (input->is_action_pressed("ui_down")) {
        input_direction.y += 1;
    }
    if (input->is_action_pressed("ui_up")) {
        input_direction.y -= 1;
    }
    
    // Debug movement (only when moving)
    if (input_direction.length() > 0) {
        Vector2 old_pos = get_position();
        UtilityFunctions::print("Player moving: ", input_direction, " Position: ", old_pos);
    }
    
    // Normalize diagonal movement
    input_direction = input_direction.normalized();
    
    // Set velocity
    velocity = input_direction * speed;
    set_velocity(velocity);
    
    // Move the character
    move_and_slide();
    
    // Confirm movement happened and check sprite position
    if (input_direction.length() > 0) {
        UtilityFunctions::print("After move_and_slide: ", get_position());
        
        if (sprite) {
            UtilityFunctions::print("Sprite global position: ", sprite->get_global_position());
            // Ensure sprite is at player position (force synchronization)
            sprite->set_global_position(get_global_position());
        }
    }
}

void Player::set_speed(float p_speed) {
    speed = p_speed;
}

float Player::get_speed() const {
    return speed;
}
