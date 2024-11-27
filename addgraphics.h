#ifndef ADDGRAPHICS_H
#define ADDGRAPHICS_H

//#include "asciiart.h"


#include <iostream>
#include "observer.h"
#include "window.h"


//#include "studio.h"

class Grid;

class GraphicsObserver : public Observer {
    int top, bottom, left, right;
    Grid* subject;
    Xwindow* window;
public:
    GraphicsObserver(int top, int bottom, int left, int right, Grid* subject);
    void notify(int n) override;
    ~GraphicsObserver();
};

#endif
