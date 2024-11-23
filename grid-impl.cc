#include "grid.h"
#include "cell.h"
#include <vector>

Grid::Grid() {
    rows = 15;
    columns = 11;
    for (int i = 0; i < rows; i++) {
        vector<Cell> newRow;
        for (int j = 0; j < rows; j++) {
            newRow.emplace_back(make_shared<Cell>(i,j));
        }
        cells.emplace_back(newRow);
    }
}