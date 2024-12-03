#include "Flower.h"
#include "Observer.h"

Flower::Flower()
{
}

bool Flower::beingCollectedByPlayable(const sf::FloatRect& bounds, std::vector<Observer*>& observers)
{
	if (Item::beingCollectedByPlayable(bounds,observers)) {
		for (Observer* observer : observers) {
			observer->collectFlower();
		}

		return true;
	}
	return false;
}
