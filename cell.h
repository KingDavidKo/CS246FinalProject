#ifndef CELL_H
#define CELL_H

#include "block.h"
#include <string>
#include <vector>
#include <memory>

class Cell {
    protected:
        int x,y;
        unique_ptr<Block> parent;
        char letter;

    public:
        Cell(int x, int y);
        void setParent();
        void swapCoords();
        void reverseRows();
        void reverseCols();

};

#endif