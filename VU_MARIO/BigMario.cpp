#include "BigMario.h"
#include "NonPlayableCharacter.h"
#include "KeyPressStrategy.h"
#include "LimitedTimeStrategy.h"
#include "Observer.h"
#include "AssetManager.h"

void BigMario::init(){
	AssetManager* instance = AssetManager::getInstance();

	std::pair<sf::Texture*, std::vector<sf::IntRect>> frames;

	frames = instance->getPlayableCharacter(PlayableCharacterType::big_mario);

	AnimationStrategy* strategy = new KeyPressStrategy(frames.first, frames.second, 1 / 60);
	AnimationStrategy* strategy2 = new LimitedTimeStrategy(frames.first, frames.second, 1 / 60);

	this->m_shape.setSize(sf::Vector2f(this->m_shape.getSize().x, this->m_shape.getSize().y + 32.f));
	this->m_position.y -= 32.f;
	this->m_animation.addStrategy(strategy);
	this->m_animation.addStrategy(strategy2);
}

BigMario::BigMario(){
	this->init();
}

BigMario::BigMario(PlayableCharacter* other) : PlayableCharacter(*other){
	this->init();
}

bool BigMario::canDestroyBrick() const{
	return true;
}

void BigMario::die(const std::vector<Observer*>& observers){
	for (Observer* observer : observers) {
		observer->mainTurnToSmall(this);
	}
}

void BigMario::hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers){
	sf::Vector2f newPosition;

	if ((character->beingHitFromBottom(this->m_shape.getGlobalBounds(), newPosition))
		|| (character->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition))
		|| (character->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition)))
	{
		for (Observer* observer : observers) {
			observer->mainTurnToSmall(this);
		}
	}
}






