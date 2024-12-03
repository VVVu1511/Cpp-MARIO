#include "GoodMushroom.h"
#include "Observer.h"

GoodMushroom::GoodMushroom()
{
}

bool GoodMushroom::beingCollectedByPlayable(const sf::FloatRect& bounds, std::vector<Observer*>& observers){
	if (Item::beingCollectedByPlayable(bounds, observers)) {
		for (Observer* observer : observers) {
			observer->collectGoodMushroom();
		}

		return true;
	}

	return false;
}
