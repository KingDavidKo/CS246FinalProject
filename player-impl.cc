#include "player.h"


Player::Player(int level): grid {make_shared<Grid>()} {
        
    text = make_shared<TextObserver>(0, 18, 0, 11, grid);
    graphics = make_shared<GraphicsObserver>(0, 18, 0, 11, grid);

    score = 0;
    level = level;
    blind = false;
    heavy = false;
    force = false;
}

void Player::incrementLevel() {
    if (level < maxlevel) {
        level++;
    }
}

void Player::decrementLevel() {
    if (level > minlevel) {
        level--;
    }
}