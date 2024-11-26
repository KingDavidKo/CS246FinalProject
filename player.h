#include <memory>
#include "grid.h"
#include "subject.h"
#include "addgraphics.h"
#include "addtext.h"

class Player {
        
        

    public:
        int score;
        
        int level;
        bool blind;
        bool heavy;
        bool force;
        Player(int level);
        shared_ptr<Grid> grid;
        shared_ptr<TextObserver> text;
        shared_ptr<GraphicsObserver> graphics;  
        //virtual ~AsciiArt();
        //virtual char charAt(int row, int col, int tick) = 0;
};