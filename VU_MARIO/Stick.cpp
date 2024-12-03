#include "Stick.h"
#include "Observer.h"

Stick::Stick(){

}

Stick::~Stick()
{
}

bool Stick::beingHitByPlayable(const sf::FloatRect& bounds, sf::Vector2f& position, std::vector<Observer*>& observers){
    if (Block::beingHitByPlayable(bounds,position,observers)) {
        
        for (Observer* observer : observers) {
            observer->hitStick();
        }

        return true;
    }

    return false;
}
