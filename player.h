#include <memory>
#include <string>
#include "grid.h"
#include "subject.h"
#include "addgraphics.h"
#include "addtext.h"
#include "level.h"
using namespace std;

class Player {
    int maxlevel = 4;
    int minlevel = -1;
    int playerNum;
    int level;
    string filename;
    public:
        Grid * grid;
        unique_ptr<Level> playerLevel;
        int score;
        bool blind;
        bool heavy;
        bool force;
        shared_ptr<TextObserver> text;
        shared_ptr<GraphicsObserver> graphics;
        Player(int playerNum, int level, string filename);
        int returnLevel();
        void incrementLevel();
        void decrementLevel();
        void updateLevel();
        shared_ptr<Block> nextBlock;
};
