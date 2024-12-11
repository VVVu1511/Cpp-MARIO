#include "GoodMushroom.h"
#include "Observer.h"

GoodMushroom::GoodMushroom()
{
}

void GoodMushroom::beingCollectedByPlayable(const std::vector<Observer*>& observers){
	//sound
	Item::beingCollectedByPlayable(observers);

	for (Observer* observer : observers) {
		observer->collectGoodMushroom();
	}
}
