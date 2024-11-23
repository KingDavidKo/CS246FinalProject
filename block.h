#include <string>
#include <vector>
#include "cell.h"
#include <memory.h>
using namespace std;

class Block {
    protected:
        int x,y;
        vector<shared_ptr<Cell>> children;

    public:
        Block(int x, int y); // Set anchor point
        void move(string dir);
        void rotateCW();
        void CCW();

};