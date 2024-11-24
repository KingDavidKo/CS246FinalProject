#include "grid.h"
#include "cell.h"
#include <vector>

Grid::Grid(): currentBlock {Block(this)} {
    rows = 18; // 15 available + 3 reserved
    columns = 11;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cells[i][j] = nullptr;
		    //unique_ptr<Cell>{}; // empty unique pointer		
        }
    }

}


void Grid::addBlock(Block block) {
    vector<Cell*> blockCells = block.getCells();
    for (int i = 0; i < 4; i++) {
        if (!cells[blockCells[i]->getGridY()][blockCells[i]->getGridX()]) {
            return;
        }
    }

    for (int i = 0; i < 4; i++) {
        cells[blockCells[i]->getGridY()][blockCells[i]->getGridX()]
          
    }

    



}

bool Grid::isGameOver() {

}


bool Grid::returnState() {

}
void Grid::setCurrent(Block& b) {

}
