#ifndef ADDTEXT_H
#define ADDTEXT_H
#include <iostream>
#include "grid.h"
#include "observer.h"
#include "subject.h"

class Grid;

class TextObserver : public Observer {
  int top, bottom, left, right;
  Grid* subject;

public:
  TextObserver(int top, int bottom, int left, int right, Grid* subject);

  ~TextObserver();

  void notify(int n) override;
};

#endif
