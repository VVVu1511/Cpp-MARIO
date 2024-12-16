#include "Mario.h"
#include "AssetManager.h"
#include "KeyPressStrategy.h"
#include "LimitedTimeStrategy.h"

void Mario::init()
{
	AssetManager* instance = AssetManager::getInstance();

	std::pair<sf::Texture*, std::vector<sf::IntRect>> frames;

	frames = instance->getPlayableCharacter(PlayableCharacterType::small_mario);

	AnimationStrategy* strategy = new KeyPressStrategy(frames.first, frames.second, 1 / 60);
	AnimationStrategy* strategy2 = new LimitedTimeStrategy(frames.first, frames.second, 1 / 60);

	this->m_shape.setSize(sf::Vector2f(32.f,32.f));
	this->m_animation.addStrategy(strategy);
	this->m_animation.addStrategy(strategy2);
}

Mario::Mario(){
	this->init();
}

Mario::Mario(PlayableCharacter* character) : PlayableCharacter(*character){
	this->init();
}

bool Mario::canAdvanced()
{
	return true;
}




