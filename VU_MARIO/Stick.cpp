#include "Stick.h"
#include "Observer.h"

Stick::Stick(){}

Stick::~Stick(){}

void Stick::specificResultAfterBeingHitFromLeft(const std::vector<Observer*>& observers, const PlayableCharacter& character){
    for (Observer* observer : observers) {
        observer->hitStick();
    }
}







