#include "Star.h"
#include "Observer.h"
#include<iostream>

Star::Star(){
	
}

void Star::beingCollectedByPlayable(PlayableCharacter* character,const std::vector<Observer*>& observers){
	//sound
	Item::beingCollectedByPlayable(character,observers);
	for (Observer* observer : observers) {
		observer->collectStar(character);
	}
}

void Star::move(const float& deltaTime){
	if(this->isMidAir() == false) this->m_position.y -= 15.f;
	
	Item::move(deltaTime);
}


