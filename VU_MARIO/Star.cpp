#include "Star.h"
#include "Observer.h"
#include<iostream>

Star::Star(){
	this->m_Vx = 1.f;
	m_jump_time = 0.3f;
}

void Star::beingCollectedByPlayable(PlayableCharacter* character,const std::vector<Observer*>& observers){
	//sound
	Item::beingCollectedByPlayable(character,observers);
	for (Observer* observer : observers) {
		observer->collectStar(character);
	}
}

void Star::move(const float& deltaTime){
	if (m_jump_time <= 0) {
		if (this->isMidAir() == false) {
			this->m_position.y -= 50.f;
			m_jump_time = 0.3f;
		}
	}

	else m_jump_time -= deltaTime;
	
	Item::move(deltaTime);
}


