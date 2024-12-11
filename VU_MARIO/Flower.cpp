#include "Flower.h"
#include "Observer.h"

Flower::Flower()
{
}

void Flower::beingCollectedByPlayable(const std::vector<Observer*>& observers)
{
	Item::beingCollectedByPlayable(observers);

	for (Observer* observer : observers) {
		observer->collectFlower();
	}
}
