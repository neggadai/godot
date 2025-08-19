#ifndef GAME_H
#define GAME_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/string.hpp>

namespace godot {

class Game : public Node2D {
    GDCLASS(Game, Node2D)

private:
    int score;
    bool game_started;

protected:
    static void _bind_methods();

public:
    Game();
    ~Game();

    void _ready() override;
    void _process(double delta) override;
    
    void start_game();
    void end_game();
    void add_score(int points);
    
    void set_score(int p_score);
    int get_score() const;
    void set_game_started(bool p_started);
    bool get_game_started() const;
};

}

#endif // GAME_H
