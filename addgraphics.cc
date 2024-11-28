#include "addgraphics.h"

const int PIXEL_SIZE = 10;

GraphicsObserver::GraphicsObserver(int top, int bottom, int left, int right, Grid* subject) : top {top}, bottom {bottom}, left {left}, right {right}, subject {subject} {
    subject->attach(this);
    // this->window = new Xwindow((right-left)*PIXEL_SIZE, (bottom-top)*PIXEL_SIZE);
}

GraphicsObserver::~GraphicsObserver() {
  if (subject) {
    subject->detach(this);  // Detach the observer when it is destroyed
  }
  delete window;
}

// Called to display the portion the observer is watching
void GraphicsObserver::notify(int n) {
    // Loop through the rectangle that this observer is watching
    /*
    if (window) {
        for (int row = top; row <= bottom; ++row) {
            for (int col = left; col <= right; ++col) {
                
                char chr = subject->getState(row, col);
                int color = Xwindow::Black; // by default black

                if (chr >= 'a' && chr <= 'z') {
                    color = Xwindow::Red;   // red
                } else if (chr >= 'A' && chr <= 'Z') {
                    color = Xwindow::Green; // green
                } else if (chr >= '0' && chr <= '9') {
                    color = Xwindow::Blue;  // blue
                } else if (chr == ' ') {
                    color = Xwindow::White; // white
                }                
                window->fillRectangle((col - left) * PIXEL_SIZE, (row - top) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color); // update window
            }
        }
    }
    */
}

