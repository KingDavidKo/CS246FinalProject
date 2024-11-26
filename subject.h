#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
using namespace std;

class Observer; // forward declaration

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach( Observer* o );
  void detach( Observer* o );
  void notifyObservers(int n);
  virtual vector<char> returnState(int n) = 0;
  virtual ~Subject() = default;
};

#endif
