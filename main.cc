#include "gameController.h"

int main(int argc, char const *argv[]) {

    // so we need to get the level from command line arguments, if there are any!
    gameController game = gameController(0, true);
    game.run();
    return 0;

}


