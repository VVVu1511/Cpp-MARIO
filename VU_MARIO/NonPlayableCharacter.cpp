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
#include "Cactus.h"
#include "KoopaTroopa.h"
#include "FireSequence.h"
#include "Boss.h"
#include "Bullet.h"

void NonPlayableCharacter::setSize(const sf::Vector2f& size) {
	this->m_shape.setSize(size);
}

NonPlayableCharacter* NonPlayableCharacter::createCharacter(const NonPlayableCharacterType& type, const sf::Vector2f& position,  const int& mapNum)
{

	NonPlayableCharacter* result = nullptr;

	switch (type)
	{
	case NonPlayableCharacterType::goomba:
		result = new Goomba;
		break;
	case NonPlayableCharacterType::koopatroopa:
		result = new KoopaTroopa(mapNum);
		break;
	case NonPlayableCharacterType::cactus:
		result = new Cactus(position);
		break;
	case NonPlayableCharacterType::boss:
		result = new Boss;
		break;
	case NonPlayableCharacterType::fire_sequence:
		result = new FireSequence;
		break;
	case NonPlayableCharacterType::bullet:
		result = new Bullet;
		break;
		//case
	//case
	default:
		result = nullptr;
		break;
	}
	
	if (result != nullptr)
	{
		result->initVariables(position, {}, {nullptr,{}});
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
		if (character->canKillNonPlayable(this->m_shape.getGlobalBounds())) {
			this->die(observers);
			return;
		}

		if (this->canKillNonPlayable(character->m_shape.getGlobalBounds())) {
			character->die(observers);
			return;
		}

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
		this->m_position.x += (this->m_speed > 0) ? 1.f : -1.f;
	}

}

void NonPlayableCharacter::specificResultAfterBeingHitByPlayable(const std::vector<Observer*>& observers, PlayableCharacter* character)
{
}

void NonPlayableCharacter::specificResultAfterBeingStoodOnByPlayable(const std::vector<Observer*>& observers, PlayableCharacter* character)
{
}

bool NonPlayableCharacter::canKillPlayable(const sf::FloatRect& bounds){
	return true;
}

bool NonPlayableCharacter::canKillNonPlayable(const sf::FloatRect& bounds){
	return false;
}

bool NonPlayableCharacter::canBeKilledByPlayable(const sf::FloatRect& bounds){
	return true;
}

void NonPlayableCharacter::shoot(const float& deltaTime, const std::vector<Observer*>& observers){}

void NonPlayableCharacter::update(const float& deltaTime, const std::vector<Observer*>& observers){
	this->shoot(deltaTime, observers);

	if(this->m_delay_dead_time == 0) this->move(deltaTime);
	
	Character::update(deltaTime,observers);
}

void NonPlayableCharacter::changeDirection(){
	this->m_speed *= -1;
}
