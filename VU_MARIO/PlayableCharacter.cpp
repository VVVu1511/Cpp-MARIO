#include "PlayableCharacter.h"
#include "Mario.h"
#include "Luigi.h"
#include "KeyPressStrategy.h"
#include "AutomaticStrategy.h"
#include "LimitedTimeStrategy.h"
#include "AssetManager.h"
#include "Item.h"
#include "Block.h"
#include "NonPlayableCharacter.h"


void PlayableCharacter::collect(Item * item, std::vector<Observer*>& observers){
	item->beingCollectedByPlayable(this->shape.getGlobalBounds(),observers);
}

void PlayableCharacter::hit(NonPlayableCharacter* character, std::vector<Observer*>& observers){
	character->beingHitByPlayable(this->shape.getGlobalBounds(),this->alive); 
}

void PlayableCharacter::standOn(NonPlayableCharacter* character, std::vector<Observer*>& observers){
	character->beingStoodOnByPlayable(this->shape.getGlobalBounds(),observers);
}

void PlayableCharacter::shoot(){

}

void PlayableCharacter::hit(Block* block, std::vector<Observer*>& observers){
	block->beingHitByPlayable(this->shape.getGlobalBounds(),this->position,observers);
}

bool PlayableCharacter::findMinForView(float& minX){
	if (position.x < minX) {
		minX = position.x;
		return true;
	}

	return false;
}

void PlayableCharacter::standInView(sf::View& view){
	float leftBound = view.getCenter().x - 600.f;
	float topBound = view.getCenter().y - 288.f;
	
	if (this->position.x < leftBound) {
		this->position.x = leftBound;
	}
	if (this->position.y < topBound) {
		this->position.y = topBound;
	}
}

void PlayableCharacter::collectGoodMushroom(){
	this->isBig = true;
}

void PlayableCharacter::collectStar(){
	this->isSuper = true;
}

void PlayableCharacter::collectFlower(){
	this->isFire = true;
}

PlayableCharacter* PlayableCharacter::createCharacter(PlayableCharacterType type, sf::Vector2f position)
{
	PlayableCharacter* result = nullptr;
	AssetManager* instance = AssetManager::getInstance();

	int character = (int)type;

	if ((character >= 1 && character <= 4) || (character >= 6 && character % 2 == 0)) {
		result = new Mario;
	}

	else {
		result = new Luigi;
	}

	if (result)
	{
		std::pair<sf::Texture*, std::vector<sf::IntRect>> images = instance->getPlayableCharacter(type);
		

		result->initVariables(position, {new KeyPressStrategy(images.first, images.second, 1.0 / 60), new LimitedTimeStrategy(images.first, images.second, 1.0 / 60), new AutomaticStrategy(images.first, images.second, 1.0 / 60)}, images);
		
		result->isBig = false;
		result->isSuper = false;
		result->isFire = false;
	}

	return result;
}

void PlayableCharacter::setCenterForView(sf::View& view){
	view.setCenter(this->position.x, view.getCenter().y);
}

void PlayableCharacter::move(const float& deltaTime){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
		this->position.y -= 10.f;
		
		animation.jump(deltaTime, sprite);
		
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->position.x += 5.f;
		if (this->position.y >= this->baseGround - this->shape.getSize().y) {
			animation.moveright(deltaTime, sprite);
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->position.x -= 5.f;
		if (this->position.y >= this->baseGround - this->shape.getSize().y) {
			animation.moveleft(deltaTime, sprite);
		}
	}
	else {
		if (this->position.y >= this->baseGround - this->shape.getSize().y) {
			animation.doNothing(this->sprite);
		}
		
	}
}

void PlayableCharacter::update(const float& deltaTime, std::vector<Observer*>& observers){
	this->move(deltaTime);
	
	Character::update(deltaTime,observers);
}

void PlayableCharacter::die(){
	Character::die();

	this->position.y -= 50.f;
}

void PlayableCharacter::reset(){
	Character::reset();
}



