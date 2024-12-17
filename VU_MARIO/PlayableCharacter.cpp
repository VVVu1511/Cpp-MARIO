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
#include "GoodBullet.h"
#include "Observer.h"

void PlayableCharacter::collect(Item * item, const std::vector<Observer*>& observers){
	sf::Vector2f newPosition;

	if ((item->beingHitFromAbove(this->m_shape.getGlobalBounds(), newPosition))
		|| (item->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition))
		|| (item->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition))) {
		
		
		item->beingCollectedByPlayable(this,observers);
	}
}

void PlayableCharacter::hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers){
	sf::Vector2f newPosition;

	if ((character->beingHitFromBottom(this->m_shape.getGlobalBounds(), newPosition))
		|| (character->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition))
		|| (character->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition)))
	{
		if (this->canBeKilledByNonPlayable() == false) {
			character->die(observers);
			return;
		}

		if (character->canKillPlayable(this->m_shape.getGlobalBounds()) == true) {
			this->die(observers);
		}
		
		else {
			character->specificResultAfterBeingHitByPlayable(observers,this);
		}
	}
}

void PlayableCharacter::standOn(NonPlayableCharacter* character, const std::vector<Observer*>& observers){
	sf::Vector2f newPosition;

	if (character->beingHitFromAbove(this->m_shape.getGlobalBounds(), newPosition) == true) {
		
		if(character->canBeKilledByPlayable(this->m_shape.getGlobalBounds()) == true) character->die(observers);
		
		character->specificResultAfterBeingStoodOnByPlayable(observers,this);
	}

}

void PlayableCharacter::shoot(const float& deltaTime, const std::vector<Observer*>& observers){}

void PlayableCharacter::hit(Block* block, const std::vector<Observer*>& observers){
	
	sf::Vector2f newPosition;
	
	bool bottom = block->beingHitFromBottom(this->m_shape.getGlobalBounds(), newPosition);
	bool left = block->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition);
	bool right = block->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition);
	

	if (block->canKillPlayable() == true) {
		if (bottom == true || left == true || right == true) {
			this->die(observers);
		}
		return;
	}
	
	if (bottom == true) {
		block->specificResultAfterBeingHitFromBottom(observers,*this);

		block->jump();

		this->m_position = newPosition;
	}

	else if (left == true) {
		block->specificResultAfterBeingHitFromLeft(observers,*this);
		this->m_position = newPosition;
		this->m_Vx = 0;
	}

	else if (right == true) {
		block->specificResultAfterBeingHitFromRight(observers,*this);
		this->m_position = newPosition;
		this->m_Vx = 0;
	}

	else {
		this->m_Vx = 5.f;
		this->m_Vy = 10.f;
	}

}

void PlayableCharacter::StandOn(Block* block, const std::vector<Observer*>& observers){
	if (block->connectToUnderground() == true)
	{
		sf::Vector2f newPosition;

		if (block->beingHitFromAbove(this->m_shape.getGlobalBounds(), newPosition)) {
			this->m_position.y += 300.f;
		}
		
	}
	else if (block->connectToGround() == true) {
		sf::Vector2f newPosition;
		if (block->beingHitFromAbove(this->m_shape.getGlobalBounds(), newPosition)) {
			this->m_position.y -= 300.f;
		}
	}
	else {
		Character::StandOn(block, observers);
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
	
}

void PlayableCharacter::collectStar(){
	
}

void PlayableCharacter::collectFlower() {

}

bool PlayableCharacter::canBeKilledByNonPlayable(){
	return true;
}

void PlayableCharacter::changeDirection(){}

void PlayableCharacter::becomeSmall(const std::vector<Observer*>& observers){
	if (canAdvanced() == false) {
		for (Observer* observer : observers) {
			observer->mainTurnToSmall(this);
		}
	}
}

bool PlayableCharacter::canViewFollow() const{
	return true;
}

bool PlayableCharacter::canDestroyBrick() const{
	return false;
}

PlayableCharacter::PlayableCharacter(){}

PlayableCharacter::PlayableCharacter(const PlayableCharacter& other){
	this->m_Vx = other.m_Vx;
	this->m_Vy = other.m_Vy;
	this->m_alive = other.m_alive;
	this->m_baseGround = other.m_baseGround;
	this->m_position = other.m_position;
	this->m_shape = other.m_shape;
	this->m_sprite = other.m_sprite;
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
		if(character > 0) result = new Luigi;
	}

	if (type == PlayableCharacterType::good_bullet) {
		result = new GoodBullet;
	}

	if (result != nullptr)
	{
		std::pair<sf::Texture*, std::vector<sf::IntRect>> images = { nullptr,{} };
		
		if(type != PlayableCharacterType::good_bullet) images = instance->getPlayableCharacter(type);
		

		result->initVariables(position, {new KeyPressStrategy(images.first, images.second, 1.0 / 60), new LimitedTimeStrategy(images.first, images.second, 1.0 / 60), new AutomaticStrategy(images.first, images.second, 1.0 / 60)}, images);
	}

	return result;
}

void PlayableCharacter::setCenterForView(sf::View& view, sf::RenderWindow* window){
	if (this->m_position.y > view.getSize().y) {
		view.setCenter(this->m_position.x, view.getSize().y + view.getSize().y / 2);
		window->clear(sf::Color::Black);
		return;
	}

	else if (this->m_position.y < view.getCenter().y - view.getSize().y / 2) {
		view.setCenter(this->m_position.x, view.getSize().y - view.getSize().y / 2);
		window->clear(sf::Color::Black);
		return;
	}

	view.setCenter(this->m_position.x, view.getCenter().y);
	/*view.setCenter(this->m_position.x, this->m_position.y);*/
}

void PlayableCharacter::move(const float& deltaTime){
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->m_position.x -= 5.f;
		m_animation.moveleft(deltaTime, this->m_sprite);
	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->m_position.x += 5.f;
		m_animation.moveright(deltaTime, this->m_sprite);
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
	if(m_delay_dead_time == 0 || this->canAdvanced() == false) this->move(deltaTime);
	
	Character::update(deltaTime,observers);
}

void PlayableCharacter::die(const std::vector<Observer*>& observers){
	Character::die(observers);
	
	this->m_alive = false;
	this->m_position.y -= 50.f;
}

void PlayableCharacter::reset(){
	Character::reset();
}



