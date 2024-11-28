#include "player.h"


Player::Player(int level, string filename): grid {new Grid()} {
    text = make_shared<TextObserver>(0, 18, 0, 11, grid);
    graphics = make_shared<GraphicsObserver>(0, 18, 0, 11, grid);
    filename = filename;
    updateLevel();
    

    score = 0;
    blind = false;
    heavy = false;
    force = false;
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

// void Player::updateLevel() {
//     if (level == 0) {
//         playerLevel.release();
//         playerLevel = make_unique<Level0>(filename, grid);
//     } else if (level == 1) {
//         playerLevel.release();
//         playerLevel = make_unique<Level1>(grid);
//     } else if (level == 2) {
//         playerLevel.release();
//         playerLevel = make_unique<Level2>(grid);
//     } else if (level == 3) {
//         playerLevel.release();
//         playerLevel = make_unique<Level3>(grid);
//     } else if (level == 4) {
//         playerLevel.release();
//         playerLevel = make_unique<Level4>(grid);
//     }
// }
void Player::updateLevel() {
    if (level == 0) {
        playerLevel = make_unique<Level0>(filename, grid); // No need for release()
    } else if (level == 1) {
        playerLevel = make_unique<Level1>(grid); // No need for release()
    } else if (level == 2) {
        playerLevel = make_unique<Level2>(grid); // No need for release()
    } else if (level == 3) {
        playerLevel = make_unique<Level3>(grid); // No need for release()
    } else if (level == 4) {
        playerLevel = make_unique<Level4>(grid); // No need for release()
    }
}


int Player::returnLevel(){
    return level;
}

