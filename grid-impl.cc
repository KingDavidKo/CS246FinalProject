#include "grid.h"
#include "cell.h"
#include <vector>

Grid::Grid() {
    rows = 18; // 15 available + 3 reserved
    columns = 11;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
		unique_ptr<Cell>{}; // empty unique pointer		
        }
    }
}
