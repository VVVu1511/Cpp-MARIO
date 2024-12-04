#include "Character.h"
#include "Mario.h"
#include "Luigi.h"
#include "Block.h"
#include "Item.h"
#include <limits>
#include "Animation.h"
#include "AssetManager.h"

void tickDownToZero(float& speed, float amount)
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

void Character::initVariables(sf::Vector2f position, std::vector<AnimationStrategy*> animationStrategy, std::pair<sf::Texture*, std::vector<sf::IntRect>> images){
	
	position.y -= images.second[0].getSize().y;
	
	this->position = position;
	
	sf::FloatRect floatRect = AssetManager::getInstance()->ToFloatRect(images.second[0]);

	this->shape.setSize(sf::Vector2f(floatRect.getSize().x,floatRect.getSize().y));
	
	for(AnimationStrategy* strategy : animationStrategy) this->animation.addStrategy(strategy);
	
	this->Vx = 0;
	this->Vy = 0;
	this->alive = true;
}

Character::Character(){}

Character::~Character(){
	
}

void Character::die(){

	animation.die(0.2, sprite);

	this->alive = false;
}

void Character::reset(){
	this->baseGround = std::numeric_limits<float>::max();
}

bool Character::isDead()
{
	return !(this->alive);
}

void Character::update(const float& deltaTime, std::vector<Observer*>& observers){
	if (this->position.y > 1000)
		this->die();
	this->position.x += Vx;
	this->position.y += Vy * deltaTime;
	if (this->position.y < this->baseGround - this->shape.getSize().y) {

	}
	else { // this sets player on ground, so make sure Vy = 0 here
		this->position.y = this->baseGround - this->shape.getSize().y;
		Vy = 0;
		is_mid_air = false;
	}

	if (this->sprite.getScale().x == -1.f) this->sprite.setPosition(sf::Vector2f(this->position.x + this->shape.getSize().x,this->position.y));
	
	else this->sprite.setPosition(this->position);

	this->shape.setPosition(this->position);

	Vy += (Vy < 10) ? 1.0 : 0;
	tickDownToZero(Vx, 1.5 * deltaTime);
}

void Character::draw(sf::RenderWindow* window){
	window->draw(sprite);
}

void Character::StandOn(Block* block, std::vector<Observer*>& observers) {
	block->beingStoodOnByCharacter(this->baseGround, this->shape.getGlobalBounds());
}