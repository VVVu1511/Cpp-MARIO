#include "FireMario.h"


void FireMario::setTimeShoot(){
	this->m_time_shoot = 1.f;
}

void FireMario::setTimeAlive(){
	this->m_delay_dead_time = 10.f;
}

FireMario::FireMario() {
	this->setTimeShoot();
	this->setTimeAlive();
}

void FireMario::shoot(const float& deltaTime){
	if (this->m_time_shoot > 0) {
		this->m_time_shoot -= deltaTime;
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {

	}

	this->setTimeShoot();
}

void FireMario::update(const float& deltaTime, const std::vector<Observer*>& observers){
	this->shoot(deltaTime);

	PlayableCharacter::update(deltaTime,observers);
}

