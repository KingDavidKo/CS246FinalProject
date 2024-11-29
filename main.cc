#include "gameController.h"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
    int level = 0;
    int seed = -1;
    bool textOnly = false;
    std::string scriptFile1 = "sequence1.txt";
    std::string scriptFile2 = "sequence2.txt";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-text") {
            textOnly = true;
        } else if (arg == "-seed" && i + 1 < argc) {
            seed = std::stoi(argv[++i]);
        } else if (arg == "-scriptfile1" && i + 1 < argc) {
            scriptFile1 = argv[++i];
        } else if (arg == "-scriptfile2" && i + 1 < argc) {
            scriptFile2 = argv[++i];
        } else if (arg == "-startlevel" && i + 1 < argc) {
            level = std::stoi(argv[++i]);
        } else {
            break;
        }
    }
    gameController game(level, textOnly, seed, scriptFile1, scriptFile2);
    game.run();
    return 0;
}
