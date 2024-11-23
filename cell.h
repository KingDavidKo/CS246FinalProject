#include "block.h"
#include <string>
#include <vector>

class Cell {
    protected:
        int x,y;
        Block parent;

    public:
        void swapCoords();
        void reverseRows();
        void reverseCols();

};