#include "Character.h"
#include "Mario.h"
#include "Luigi.h"
#include "Block.h"
#include "Item.h"
#include <limits>
#include "Animation.h"
#include "AssetManager.h"
#include "View.h"

void Character::tickDownToZero(float& speed, float amount)
{
	if (speed > 0)
	{
		speed -= amount;
		speed = (speed < 0) ? 0 : speed;
	}
	else if (speed < 0)
	{
		speed += amount;
		speed = (speed > 0) ? 0 : speed;
	}
}

bool Character::standInView(View view) {
	return view.containObjectAt(this->m_shape.getGlobalBounds());
}

bool Character::canAdvanced(){
	return false;
}

void Character::initVariables(const sf::Vector2f &position, const std::vector<AnimationStrategy*>& animationStrategy,const std::pair<sf::Texture*, std::vector<sf::IntRect>> &images){
	
	sf::Vector2f tempPos = position;

	this->m_baseGround= tempPos.y;

	this->m_position = tempPos;
	
	if (images.first != nullptr && images.second.empty() == false) {
		tempPos.y -= images.second[0].getSize().y;
		sf::FloatRect floatRect = AssetManager::getInstance()->ToFloatRect(images.second[0]);
		this->m_shape.setSize(sf::Vector2f(floatRect.getSize().x, floatRect.getSize().y));
		
		for(AnimationStrategy* strategy : animationStrategy) this->m_animation.addStrategy(strategy);
	}

	
	this->m_Vx = 0;
	this->m_Vy = 0;
	this->m_alive = true;
	this->m_delay_dead_time = 0;
}

bool Character::isMidAir(){
	return this->m_position.y < this->m_baseGround - this->m_shape.getSize().y;
}

Character::Character(){}

Character::~Character(){
	
}

void Character::die(const std::vector<Observer*>& observers) {

	this->m_animation.die(0.2, m_sprite);
	
	this->m_delay_dead_time = 0.5;
}

void Character::reset(){
	this->m_baseGround = std::numeric_limits<float>::max();
}

bool Character::isDead()
{
	return this->m_delay_dead_time > 0;
}

void Character::update(const float& deltaTime, const std::vector<Observer*>& observers){
	float dT = deltaTime * 60;
	
	tickDownToZero(m_Vx, 1 * dT);
	
	if (this->m_position.y > 1000) this->die(observers);

	this->m_position.x += (abs(m_Vx * dT) > 5.f) ? (m_Vx > 0 ? 5.f : -5.f) : m_Vx * dT;
	this->m_position.y += (abs(m_Vy * dT) > 10.f) ? (m_Vy > 0 ? 10.f : -10.f) : m_Vy * dT;

	
	if (this->m_delay_dead_time > 0 && this->canAdvanced() == true) {
		this->m_delay_dead_time -= deltaTime;
		this->m_animation.die(deltaTime,this->m_sprite);
	}

	if (this->m_position.y < this->m_baseGround - this->m_shape.getSize().y) {
		this->m_Vy += (m_Vy < 8) ? 0.75 * dT : 0;
	}

	else {
		if(this->m_position.y - this->m_baseGround < 15.f) this->m_position.y = this->m_baseGround - this->m_shape.getSize().y;
		
		this->m_Vy = 0;
		is_jumping = false;
		is_max_jump_speed = false;
	}

	if (this->m_sprite.getScale().x == -1.f) this->m_sprite.setPosition(sf::Vector2f(this->m_position.x + this->m_shape.getSize().x, this->m_position.y));

	else this->m_sprite.setPosition(this->m_position);


	this->m_shape.setPosition(this->m_position);
}

void Character::draw(sf::RenderWindow* window){
	window->draw(this->m_sprite);
}

void Character::StandOn(Block* block,const std::vector<Observer*>& observers) {
	sf::Vector2f newPosition;

	if (block->underObjectAt(this->m_shape.getGlobalBounds(),newPosition)) {
		if (newPosition.y < this->m_baseGround) {
			this->m_baseGround = newPosition.y;
		}
	}
}