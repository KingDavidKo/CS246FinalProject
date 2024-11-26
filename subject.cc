#include "subject.h"
#include "observer.h"
#include <vector>


// Adds new observer in vector
void Subject::attach( Observer* o ) {
    observers.emplace_back(o);
}

// Finds the observer and removes it from vector
void Subject::detach( Observer* o ) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            return;
        }
    }
}

// Notifies all observers
void Subject::notifyObservers(int n) {
    for (Observer* observer : observers) {
        observer->notify(n);
    }
}
