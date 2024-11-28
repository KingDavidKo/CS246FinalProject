#include "addtext.h"
using namespace std;


TextObserver::TextObserver(int top, int bottom, int left, int right, Grid* subject): top {top}, bottom {bottom}, left {left}, right {right}, subject {subject} {
  subject->attach(this); // Attach to subject
}

TextObserver::~TextObserver() {
  if (subject) {
    subject->detach(this);  // Detach the observer when it is destroyed
  }
}

// Called to display the portion the observer is watching
void TextObserver::notify(int n) {
  vector<char> v = subject->returnState(n); 

  for (int i = 0; i < 11; i++) {
    cout << v[i];
  }
}
