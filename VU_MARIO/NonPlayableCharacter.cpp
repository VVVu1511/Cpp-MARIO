#include "NonPlayableCharacter.h"
#include "Goomba.h"
#include "KoopaTroopa.h"
#include "AutomaticStrategy.h"
#include "AssetManager.h"
#include "LimitedTimeStrategy.h"
#include "Block.h"
#include "Observer.h"
#include "KeyPressStrategy.h"
#include "View.h"

NonPlayableCharacter* NonPlayableCharacter::createCharacter(const NonPlayableCharacterType& type, const sf::Vector2f& m_position)
{

	NonPlayableCharacter* result = nullptr;

	switch (type)
	{
	case NonPlayableCharacterType::goomba:
		result = new Goomba;
		break;
	case NonPlayableCharacterType::koopatroopa:
		result = new KoopaTroopa;
		break;
	//case
	//case
	default:
		result = nullptr;
		break;
	}
	
	if (result)
	{
		std::pair<sf::Texture*, std::vector<sf::IntRect>> images = AssetManager::getInstance()->getNonPlayableCharacter(type);
		
		result->initVariables(m_position, {new LimitedTimeStrategy(images.first,images.second,1.0 / 60),new AutomaticStrategy(images.first,images.second,1.0 / 60) }, images);
	}

	return result;
}

void NonPlayableCharacter::move(const float& deltaTime){
	this->m_position.x += this->m_speed;

	m_animation.changeAutomatically(deltaTime, this->m_sprite);

	if (this->m_speed < 0) {
		m_sprite.setScale(-1.f, 1.f);
	}
	else {
		m_sprite.setScale(1.f, 1.f);
	}

}

void NonPlayableCharacter::hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers){
	sf::Vector2f newPosition;

	bool right = character->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition);
	bool left = character->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition);

	if (character->beingHitFromBottom(this->m_shape.getGlobalBounds(), newPosition) == true) {
		this->m_position = newPosition;
	}
	
	else if (right == true || left == true)
	{
		this->m_position = newPosition;
		
		this->changeDirection();
		character->changeDirection();
		
		if (this->m_speed < 0) {
			this->m_position.x -= 1.f;
			character->m_position.x += 1.f;
		}
		else {
			this->m_position.x += 1.f;
			character->m_position.x -= 1.f;
		}
	}

}

void NonPlayableCharacter::hit(Block* block, const std::vector<Observer*>& observers){
	sf::Vector2f newPosition;

	if (block->beingHitFromBottom(this->m_shape.getGlobalBounds(), newPosition) == true) {
		this->m_position = newPosition;
	}

	else if ((block->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition)) == true
		|| (block->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition)) == true)
	{
		this->m_position = newPosition;
		this->changeDirection();
	}

}

void NonPlayableCharacter::specificResultAfterBeingHit(const std::vector<Observer*>& observers, const sf::FloatRect& bounds){

}

void NonPlayableCharacter::specificResultAfterBeingStoodOn(const std::vector<Observer*>& observers, const sf::FloatRect& bounds){}

bool NonPlayableCharacter::canKill(){
	return true;
}

void NonPlayableCharacter::update(const float& deltaTime, const std::vector<Observer*>& observers){
	this->move(deltaTime);

	Character::update(deltaTime,observers);
	
}

void NonPlayableCharacter::changeDirection(){
	this->m_speed *= -1;
}
