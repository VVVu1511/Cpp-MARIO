#include "Mario.h"

Mario::Mario(){}

void Mario::turnToSmall(){
	PlayableCharacter::turnToSmall();

	AssetManager* instance = AssetManager::getInstance();

	std::pair<sf::Texture*, std::vector<sf::IntRect>> frames;

	frames = instance->getPlayableCharacter(PlayableCharacterType::small_mario);

	this->m_animation.changeTexture(frames.first, frames.second);
}

void Mario::collectGoodMushroom(){
	AssetManager* instance = AssetManager::getInstance();

	PlayableCharacter::collectGoodMushroom();

	std::pair<sf::Texture*, std::vector<sf::IntRect>> frames;

	if(isFire) frames = instance->getPlayableCharacter(PlayableCharacterType::big_fire_mario);
	else if(isSuper) frames = instance->getPlayableCharacter(PlayableCharacterType::big_super_mario);
	else frames = instance->getPlayableCharacter(PlayableCharacterType::big_mario);
	
	this->m_animation.changeTexture(frames.first, frames.second);
}

void Mario::collectStar(){
	AssetManager* instance = AssetManager::getInstance();

	PlayableCharacter::collectStar();

	std::pair<sf::Texture*, std::vector<sf::IntRect>> frames;

	if (this->isBig) {
		frames = instance->getPlayableCharacter(PlayableCharacterType::big_super_mario);
	}

	else {
		frames = instance->getPlayableCharacter(PlayableCharacterType::small_super_mario);
	}

	this->m_animation.changeTexture(frames.first, frames.second);
}

void Mario::collectFlower(){
	AssetManager* instance = AssetManager::getInstance();

	PlayableCharacter::collectFlower();

	std::pair<sf::Texture*, std::vector<sf::IntRect>> frames;

	if (this->isBig) {
		frames = instance->getPlayableCharacter(PlayableCharacterType::big_fire_mario);
	}

	else frames = instance->getPlayableCharacter(PlayableCharacterType::small_fire_mario);

	this->m_animation.changeTexture(frames.first, frames.second);
}




