#include "Brick.h"

Brick::Brick()
{
}

void Brick::jump(){
    this->m_position.y -= 20.f;
}

void Brick::beingHitFromBottomByBigMario(const std::vector<Observer*>& observers){
    this->die();
}




