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

void PlayableCharacter::collect(Item * item, const std::vector<Observer*>& observers){
	sf::Vector2f newPosition;

	if ((item->beingHitFromAbove(this->m_shape.getGlobalBounds(), newPosition))
		|| (item->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition))
		|| (item->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition))) {
		
		
		item->beingCollectedByPlayable(observers);
	}
}

void PlayableCharacter::hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers){
	sf::Vector2f newPosition;

	if ((character->beingHitFromBottom(this->m_shape.getGlobalBounds(), newPosition))
		|| (character->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition))
		|| (character->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition)))
	{

		if (this->isSuper) {
			character->die();
			return;
		}
		
		if (character->canKill()) {
			if (!this->isBig) {
				this->die();
				return;
			}

			this->turnToSmall();
		}
		
		else {
			character->specificResultAfterBeingHit(observers,this->m_shape.getGlobalBounds());
		}
	}
}

void PlayableCharacter::standOn(NonPlayableCharacter* character, const std::vector<Observer*>& observers){
	sf::Vector2f newPosition;

	if (character->beingHitFromAbove(this->m_shape.getGlobalBounds(), newPosition) == true) {
		character->die();
		character->specificResultAfterBeingStoodOn(observers,this->m_shape.getGlobalBounds());
	}

}

void PlayableCharacter::shoot(){
	if (this->isFire) {

	}
}

void PlayableCharacter::hit(Block* block, const std::vector<Observer*>& observers){
	
	sf::Vector2f newPosition;

	if (block->beingHitFromBottom(this->m_shape.getGlobalBounds(),newPosition)) {

		if(this->isBig) block->beingHitFromBottomByBigMario(observers);

		block->specificResultAfterBeingHitFromBottom(observers);

		block->jump();

		this->m_position = newPosition;
	}

	else if (block->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition)) {
		block->specificResultAfterBeingHitFromLeft(observers);
		this->m_position = newPosition;
		this->m_Vx = 0;
	}

	else if (block->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition)) {
		block->specificResultAfterBeingHitFromRight(observers);
		this->m_position = newPosition;
		this->m_Vx = 0;
	}

	else {
		this->m_Vx = 5.f;
		this->m_Vy = 10.f;
	}

}

bool PlayableCharacter::findMinForView(float& minX){
	if (this->m_position.x < minX) {
		minX = m_position.x;
		return true;
	}

	return false;
}

void PlayableCharacter::standInsideView(sf::View& view){
	float leftBound = view.getCenter().x - 600.f;
	float topBound = view.getCenter().y - 288.f;
	
	if (this->m_position.x < leftBound) {
		this->m_position.x = leftBound;
	}
	if (this->m_position.y < topBound) {
		this->m_position.y = topBound;
	}
}

void PlayableCharacter::collectGoodMushroom(){
	if(!this->isBig) this->m_shape.setSize(sf::Vector2f(this->m_shape.getSize().x,this->m_shape.getSize().y * 2));

	this->isBig = true;
}

void PlayableCharacter::collectStar(){
	this->isSuper = true;
}

void PlayableCharacter::collectFlower(){
	this->isFire = true;
}

void PlayableCharacter::turnToSmall(){
	this->m_shape.setSize(sf::Vector2f(32.f, 32.f));
	this->isBig = false;
}

PlayableCharacter* PlayableCharacter::createCharacter(const PlayableCharacterType &type, const sf::Vector2f position)
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
	view.setCenter(this->m_position.x, view.getCenter().y);
}

void PlayableCharacter::move(const float& deltaTime){
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->m_position.x -= m_Vx;
		if (m_Vx > 0) m_animation.moveleft(deltaTime, this->m_sprite);
	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->m_position.x += m_Vx;
		if(m_Vx > 0) m_animation.moveright(deltaTime, this->m_sprite);
	}
	
	else {
		m_animation.doNothing(this->m_sprite);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->m_position.y -= 10.f;
	}

	if (this->isMidAir()) {
		m_animation.jump(deltaTime,this->m_sprite);
	}
}

void PlayableCharacter::update(const float& deltaTime, const std::vector<Observer*>& observers){
	this->move(deltaTime);
	
	Character::update(deltaTime,observers);
}

void PlayableCharacter::die(){
	Character::die();
	this->m_alive = false;
	this->m_position.y -= 50.f;
}

void PlayableCharacter::reset(){
	Character::reset();
}



