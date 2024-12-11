#include "Stick.h"
#include "Observer.h"

Stick::Stick(){}

Stick::~Stick(){}

void Stick::specificResultAfterBeingHitFromLeft(const std::vector<Observer*>& observers){
    for (Observer* observer : observers) {
        observer->hitStick();
    }
}

void Stick::specificResultAfterBeingHitFromRight(const std::vector<Observer*>& observers){
    this->specificResultAfterBeingHitFromLeft(observers);
}





