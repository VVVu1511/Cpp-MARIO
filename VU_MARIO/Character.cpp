#include "Character.h"
#include "Mario.h"
#include "Luigi.h"
#include "Block.h"
#include "Item.h"
#include <limits>
#include "Animation.h"
#include "AssetManager.h"
#include "View.h"

bool Character::standInView(View view) {
	return view.containObjectAt(this->m_shape.getGlobalBounds());
}

void Character::initVariables(const sf::Vector2f &position, const std::vector<AnimationStrategy*>& animationStrategy,const std::pair<sf::Texture*, std::vector<sf::IntRect>> &images){
	
	sf::Vector2f tempPos = position;

	tempPos.y -= images.second[0].getSize().y;
	
	this->m_position = tempPos;
	
	sf::FloatRect floatRect = AssetManager::getInstance()->ToFloatRect(images.second[0]);

	this->m_shape.setSize(sf::Vector2f(floatRect.getSize().x,floatRect.getSize().y));
	
	for(AnimationStrategy* strategy : animationStrategy) this->m_animation.addStrategy(strategy);
	
	this->m_Vx = 0;
	this->m_Vy = 0;
	this->m_alive = true;

}

bool Character::isMidAir(){
	return this->m_position.y < this->m_baseGround - this->m_shape.getSize().y;
}

Character::Character(){}

Character::~Character(){
	
}

void Character::die(){

	m_animation.die(0.2, m_sprite);

	this->m_alive = false;
}

void Character::reset(){
	this->m_baseGround = std::numeric_limits<float>::max();
}

bool Character::isDead()
{
	return !(this->m_alive);
}

void Character::update(const float& deltaTime, const std::vector<Observer*>& observers){
	
	if (this->m_position.y < this->m_baseGround - this->m_shape.getSize().y) {
		this->m_position.y += 5.f;
	}

	else {
		this->m_position.y = this->m_baseGround - this->m_shape.getSize().y;
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