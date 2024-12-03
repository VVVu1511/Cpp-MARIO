#include "Coin.h"
#include "Observer.h"

Coin::Coin()
{
}

bool Coin::beingCollectedByPlayable(const sf::FloatRect& bounds, std::vector<Observer*>& observers){
	if (Item::beingCollectedByPlayable(bounds,observers)) {
		for (Observer* observer : observers) {
			observer->collectCoins();
		}

		return true;
	}

	return false;
}

