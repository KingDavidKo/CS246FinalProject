#include "player.h"


Player::Player(int level) {
    score = 0;
    grid = make_shared<Grid>();
    level = level;
}