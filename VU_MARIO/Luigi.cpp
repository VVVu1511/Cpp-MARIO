#include "Luigi.h"
#include "AssetManager.h"
#include <vector>

Luigi::Luigi(){}

void Luigi::turnToSmall(){
	PlayableCharacter::turnToSmall();

	AssetManager* instance = AssetManager::getInstance();

	std::pair<sf::Texture*, std::vector<sf::IntRect>> frames;

	frames = instance->getPlayableCharacter(PlayableCharacterType::small_luigi);

	this->m_animation.changeTexture(frames.first, frames.second);
}

void Luigi::move(){
}

void Luigi::collectGoodMushroom(){
	AssetManager* instance = AssetManager::getInstance();

	PlayableCharacter::collectGoodMushroom();

	std::pair<sf::Texture*, std::vector<sf::IntRect>> frames;

	frames = instance->getPlayableCharacter(PlayableCharacterType::big_luigi);

	this->m_animation.changeTexture(frames.first, frames.second);
}

void Luigi::collectStar(){
	AssetManager* instance = AssetManager::getInstance();

	PlayableCharacter::collectStar();

	std::pair<sf::Texture*, std::vector<sf::IntRect>> frames;

	if (this->isBig) {
		frames = instance->getPlayableCharacter(PlayableCharacterType::big_super_luigi);
	}

	else {
		frames = instance->getPlayableCharacter(PlayableCharacterType::small_luigi);
	}

	this->m_animation.changeTexture(frames.first, frames.second);
}

void Luigi::collectFlower(){
	AssetManager* instance = AssetManager::getInstance();

	PlayableCharacter::collectFlower();

	std::pair<sf::Texture*, std::vector<sf::IntRect>> frames;

	if (this->isBig) {
		frames = instance->getPlayableCharacter(PlayableCharacterType::big_fire_luigi);
	}

	else frames = instance->getPlayableCharacter(PlayableCharacterType::small_luigi);

	this->m_animation.changeTexture(frames.first, frames.second);
}
