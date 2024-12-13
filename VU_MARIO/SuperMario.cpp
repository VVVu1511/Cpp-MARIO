#include "SuperMario.h"
#include "NonPlayableCharacter.h"

void SuperMario::hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers){
	sf::FloatRect m_bounds = this->m_shape.getGlobalBounds();
	sf::Vector2f newPosition;

	if (character->beingHitFromLeftBy(m_bounds,newPosition) == true || character->beingHitFromRightBy(m_bounds,newPosition) == true) {
		character->die();
	}
}
