#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class Player : public CharacterBody2D {
    GDCLASS(Player, CharacterBody2D)

private:
    float speed;
    Vector2 velocity;
    Sprite2D* sprite;
    Camera2D* camera;

protected:
    static void _bind_methods();

public:
    Player();
    ~Player();

    void _ready() override;
    void _physics_process(double delta) override;
    
    void set_speed(float p_speed);
    float get_speed() const;
};

}

#endif // PLAYER_H
