#include <memory>
#include "grid.h"

class Player {
    protected:
        int score;
        shared_ptr<Grid> grid;
        int level;
        bool blind;
        bool heavy;
        bool force;
    

    public:
        Player(int level);
        //virtual ~AsciiArt();
        //virtual char charAt(int row, int col, int tick) = 0;
};