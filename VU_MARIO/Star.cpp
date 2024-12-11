#include "Star.h"
#include "Observer.h"

Star::Star(){}

void Star::beingCollectedByPlayable(const std::vector<Observer*>& observers){
	//sound
	Item::beingCollectedByPlayable(observers);
	for (Observer* observer : observers) {
			observer->collectStar();
	}
}

void Star::move(const float& deltaTime){
	Item::move(deltaTime);

	this->m_position.y -= 10.f;
}
