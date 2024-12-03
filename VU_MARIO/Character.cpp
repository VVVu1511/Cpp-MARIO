#include "Character.h"
#include "Mario.h"
#include "Luigi.h"
#include "Block.h"
#include "Item.h"
#include <limits>
#include "Animation.h"
#include "AssetManager.h"

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
	Vy = 0;

	if (this->position.y < this->baseGround - this->shape.getSize().y) {
		this->position.y += 5.f;
	}
	else {
		this->position.y = this->baseGround - this->shape.getSize().y;
	}

	if (this->sprite.getScale().x == -1.f) this->sprite.setPosition(sf::Vector2f(this->position.x + this->shape.getSize().x,this->position.y));
	
	else this->sprite.setPosition(this->position);

	this->shape.setPosition(this->position);
}

void Character::draw(sf::RenderWindow* window){
	window->draw(sprite);
}

void Character::StandOn(Block* block, std::vector<Observer*>& observers) {
	block->beingStoodOnByCharacter(this->baseGround, this->shape.getGlobalBounds());
}