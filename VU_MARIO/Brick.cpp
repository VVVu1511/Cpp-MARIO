#include "Brick.h"
#include "PlayableCharacter.h"

Brick::Brick()
{
}

void Brick::jump(){
    this->m_position.y -= 6.f;
}

void Brick::specificResultAfterBeingHitFromBottom(const std::vector<Observer*>& observers, const PlayableCharacter& character){
    if (character.canDestroyBrick()) {
        this->die();
    }
}






