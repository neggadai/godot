#include "game.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Game::_bind_methods() {
    // Simplified binding for Godot 4.4 compatibility
    // Methods can be called from C++ but not exposed to GDScript for now
}

Game::Game() {
    score = 0;
    game_started = false;
}

Game::~Game() {
    // Cleanup if needed
}

void Game::_ready() {
    UtilityFunctions::print("Game initialized!");
}

void Game::_process(double delta) {
    // Game logic updates
    if (game_started) {
        // Game running logic here
    }
}

void Game::start_game() {
    game_started = true;
    score = 0;
    UtilityFunctions::print("Game started!");
}

void Game::end_game() {
    game_started = false;
    UtilityFunctions::print("Game ended! Final score: ", score);
}

void Game::add_score(int points) {
    score += points;
}

void Game::set_score(int p_score) {
    score = p_score;
}

int Game::get_score() const {
    return score;
}

void Game::set_game_started(bool p_started) {
    game_started = p_started;
}

bool Game::get_game_started() const {
    return game_started;
}
