#include "FireMario.h"
#include "Observer.h"
#include "KeyPressStrategy.h"
#include "AssetManager.h"
#include "LimitedTimeStrategy.h"

void FireMario::setTimeShoot(){
	this->m_time_shoot = 1.f;
}

void FireMario::init(){
	this->m_time_shoot = 0.f;
	this->setTimeAlive();

	AssetManager* instance = AssetManager::getInstance();

	std::pair<sf::Texture*, std::vector<sf::IntRect>> frames;

	frames = instance->getPlayableCharacter(PlayableCharacterType::small_fire_mario);

	AnimationStrategy* strategy = new KeyPressStrategy(frames.first, frames.second, 1 / 60);
	AnimationStrategy* strategy2 = new LimitedTimeStrategy(frames.first, frames.second, 1 / 60);

	this->m_shape.setSize(sf::Vector2f(32.f, 32.f));
	this->m_animation.addStrategy(strategy);
	this->m_animation.addStrategy(strategy2);
}

void FireMario::setTimeAlive(){
	this->m_delay_dead_time = 10.f;
}

FireMario::FireMario() {
	init();
}

FireMario::FireMario(PlayableCharacter* character) : PlayableCharacter(*character){
	this->init();
}

void FireMario::shoot(const float& deltaTime, const std::vector<Observer*>& observers){
	if (this->m_time_shoot > 0) {
		this->m_time_shoot -= deltaTime;
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		
		for (Observer* observer : observers) {
			observer->mainShooting(this->m_position, this->m_Vx);
		}
		
		this->setTimeShoot();
	}
}

void FireMario::update(const float& deltaTime, const std::vector<Observer*>& observers){
	this->shoot(deltaTime,observers);
	
	if (m_delay_dead_time > 0) {
		this->m_delay_dead_time -= deltaTime;
	}

	else {
		this->becomeSmall(observers);
	}

	PlayableCharacter::update(deltaTime,observers);
}


