#include "Flower.h"
#include "Observer.h"

Flower::Flower()
{
}

void Flower::beingCollectedByPlayable(PlayableCharacter* character,const std::vector<Observer*>& observers)
{
	Item::beingCollectedByPlayable(character,observers);

	for (Observer* observer : observers) {
		observer->collectFlower(character);
	}
}
