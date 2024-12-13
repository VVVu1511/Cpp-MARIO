#include "BigMario.h"
#include "NonPlayableCharacter.h"

void BigMario::turnToSmall(){

}

void BigMario::hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers){
	sf::FloatRect m_bounds = this->m_shape.getGlobalBounds();
	sf::Vector2f newPosition;

	if (character->canKillPlayable(m_bounds) == false) {
		PlayableCharacter::hit(character, observers);
		return;
	}

	if (character->beingHitFromLeftBy(m_bounds,newPosition) || character->beingHitFromRightBy(m_bounds, newPosition)) {
		this->turnToSmall();
	}
}

bool BigMario::canDestroyBrick() const{
	return true;
}


