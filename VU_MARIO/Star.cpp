#include "Star.h"
#include "Observer.h"

Star::Star()
{

}

bool Star::beingCollectedByPlayable(const sf::FloatRect& bounds, std::vector<Observer*>& observers){
	if (Item::beingCollectedByPlayable(bounds, observers)) {
		for (Observer* observer : observers) {
			observer->collectStar();
		}

		return true;
	}

	return false;
}
