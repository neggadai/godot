#ifndef SIMPLE_OSU_GAME_H
#define SIMPLE_OSU_GAME_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/color_rect.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/variant/string.hpp>

namespace godot {

class SimpleOsuGame : public Node2D {
    GDCLASS(SimpleOsuGame, Node2D)

private:
    // Game state
    bool game_active;
    int score;
    int combo;
    float game_time;
    
    // UI elements
    ColorRect* background;
    Label* title_label;
    Label* score_label;
    Label* combo_label;
    Label* instructions_label;
    
    // Simple hit circles
    struct SimpleHitCircle {
        ColorRect* visual;
        Vector2 position;
        float spawn_time;
        float hit_time;
        bool is_active;
        bool is_hit;
        
        SimpleHitCircle() : visual(nullptr), position(), spawn_time(0), hit_time(0), is_active(false), is_hit(false) {}
    };
    
    static const int MAX_CIRCLES = 10;
    SimpleHitCircle circles[MAX_CIRCLES];
    int active_circle_count;
    
    // Spawn timing
    float next_spawn_time;
    float spawn_interval;

protected:
    static void _bind_methods();

public:
    SimpleOsuGame();
    ~SimpleOsuGame();

    void _ready() override;
    void _process(double delta) override;
    
    // Game logic
    void start_game();
    void spawn_circle();
    void update_circles(float delta_time);
    void check_circle_hit(Vector2 click_pos);
    void update_ui();
    
    // Utilities
    ColorRect* create_circle(Vector2 pos, Color color, float size);
};

}

#endif // SIMPLE_OSU_GAME_H
