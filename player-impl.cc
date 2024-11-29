#include "player.h"


Player::Player(int playerNum, int level, string filename): playerNum{playerNum}, grid {new Grid()} {
    text = make_shared<TextObserver>(0, 18, 0, 11, grid);
    this->level = level;
    this->filename = filename;
    updateLevel();
    grid->setCurrent(playerLevel->generateBlock());
    if (playerNum == 1) {
        this->nextBlock = playerLevel->generateBlock();
    }
    this->score = 0;
    this->blind = false;
    this->heavy = false;
    this->force = false;
}

void Player::incrementLevel() {
    if (level < maxlevel) {
        level++;
    }
    updateLevel();
}

void Player::decrementLevel() {
    if (level > minlevel) {
        level--;
    }
    this->updateLevel();
}

void Player::updateLevel() {
    if (level == 0) {
        playerLevel.reset(); // should be reset, not release
        playerLevel = make_unique<Level0>(filename, grid);
    } else if (level == 1) {
        playerLevel.reset();
        playerLevel = make_unique<Level1>(grid);
    } else if (level == 2) {
        playerLevel.reset();
        playerLevel = make_unique<Level2>(grid);
    } else if (level == 3) {
        playerLevel.reset();
        playerLevel = make_unique<Level3>(grid);
    } else if (level == 4) {
        playerLevel.reset();
        playerLevel = make_unique<Level4>(grid);
    }
    grid->setLevel(level); // sets the grid's level accordingly
}
int Player::returnLevel(){
    return level;
}

