//need adjustment

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

NonPlayableCharacter* NonPlayableCharacter::createCharacter(NonPlayableCharacterType type, sf::Vector2f position)
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
		
		result->initVariables(position, {new LimitedTimeStrategy(images.first,images.second,1.0 / 60),new AutomaticStrategy(images.first,images.second,1.0 / 60) }, images);
	}

	return result;
}

void NonPlayableCharacter::move(const float& deltaTime){
	this->position.x += this->speed;

	animation.changeAutomatically(deltaTime, this->sprite);

	if (this->speed < 0) {
		sprite.setScale(-1.f, 1.f);
	}
	else {
		sprite.setScale(1.f, 1.f);
	}

}

void NonPlayableCharacter::hit(NonPlayableCharacter* character, std::vector<Observer*>& observers){
	character->beingHitByNonPlayable(this->shape.getGlobalBounds(), this->speed,this->alive);
}

void NonPlayableCharacter::hit(Block* block, std::vector<Observer*>& observers){
	block->beingHitByNonPlayable(this->shape.getGlobalBounds(),this->position, observers,this->speed);
}

bool NonPlayableCharacter::beingHitByNonPlayable(const sf::FloatRect& bounds, float& o_speed, bool& alive){
	sf::FloatRect m_bounds = this->shape.getGlobalBounds();

	if (bounds.intersects(m_bounds)) {
		o_speed *= -1.001;
		this->speed *= -1.002;
		
		if (m_bounds.left < bounds.left) {
			this->position.x = bounds.left - this->shape.getSize().x - 2.f;
		}

		else if(m_bounds.left > bounds.left) {
			this->position.x = bounds.left + bounds.width + 2.f;
		}
		
		return true;
	}
	return false;
}

void NonPlayableCharacter::update(const float& deltaTime, std::vector<Observer*>& observers){
	this->move(deltaTime);

	Character::update(deltaTime,observers);
	
}

bool NonPlayableCharacter::standInView(View view){
	return view.containObjectAt(this->shape.getGlobalBounds());
}

bool NonPlayableCharacter::beingStoodOnByPlayable(const sf::FloatRect& bounds, std::vector<Observer*>& observers){
	sf::FloatRect m_bounds = this->shape.getGlobalBounds();

	bool horizontalOverlap = bounds.left + bounds.width > m_bounds.left && bounds.left < m_bounds.left + m_bounds.width;

	bool verticalOverlap = bounds.top + bounds.height >= m_bounds.top && bounds.top + bounds.height <= m_bounds.top + 5.f;

	if (horizontalOverlap && verticalOverlap) {
		this->die();

		for (Observer* observer : observers) {
			observer->killEnemies();
		}

		return true;
	}

	return false;
}


void NonPlayableCharacter::beingHitByPlayable(const sf::FloatRect& bounds, bool& alive){
	sf::FloatRect m_bounds = this->shape.getGlobalBounds();

	if (this->alive && bounds.intersects(m_bounds)) {
		alive = false; 
	}
}

void NonPlayableCharacter::beingHitByBlock(const sf::FloatRect& bounds, std::vector<Observer*>& observers){
	sf::FloatRect m_bounds = this->shape.getGlobalBounds();

	if (m_bounds.intersects(bounds)) {
		for (Observer* observer : observers) {
			observer->killEnemies();
		}
		
		this->die();
	}
}
