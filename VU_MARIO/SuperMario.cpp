#include "SuperMario.h"
#include "AssetManager.h"
#include "NonPlayableCharacter.h"
#include "KeyPressStrategy.h"
#include "LimitedTimeStrategy.h"
#include "Observer.h"

void SuperMario::die(const std::vector<Observer*>& observers){}

bool SuperMario::canBeKilledByNonPlayable(){
	return false;
}

void SuperMario::init(){
	AssetManager* instance = AssetManager::getInstance();
	this->m_delay_dead_time = 10.f;

	std::pair<sf::Texture*, std::vector<sf::IntRect>> frames;

	frames = instance->getPlayableCharacter(PlayableCharacterType::small_super_mario);

	AnimationStrategy* strategy = new KeyPressStrategy(frames.first, frames.second, 1 / 60);
	AnimationStrategy* strategy2 = new LimitedTimeStrategy(frames.first, frames.second, 1 / 60);

	this->m_shape.setSize(sf::Vector2f(32.f, 32.f));
	this->m_animation.addStrategy(strategy);
	this->m_animation.addStrategy(strategy2);
}

SuperMario::SuperMario() {
	this->init();
}

SuperMario::SuperMario(PlayableCharacter* character) : PlayableCharacter(*character){
	this->init();

	std::cout << this->m_position.x << " " << this->m_position.y;
}

void SuperMario::update(const float& deltaTime, const std::vector<Observer*>& observers) {
	if (m_delay_dead_time > 0) {
		this->m_delay_dead_time -= deltaTime;
	}

	else {
		this->becomeSmall(observers);
		return;
	}

	PlayableCharacter::update(deltaTime, observers);
}