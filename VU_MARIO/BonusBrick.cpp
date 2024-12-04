#include "BonusBrick.h"
#include "AutomaticStrategy.h"
#include "Animation.h"
#include "Observer.h"
#include "AssetManager.h"

ItemType BonusBrick::getRandomItem(){
	int randValue = rand() % 100; 

	if (randValue < 10) {
		return ItemType::star; 
	}
	else if (randValue < 30) {
		return ItemType::flower; 
	}
	else if (randValue < 60) {
		return ItemType::mushroom; 
	}
	
	return ItemType::coin; 
}

BonusBrick::BonusBrick(){
	type = getRandomItem();
}

BonusBrick::~BonusBrick(){}


void BonusBrick::twinkle(const float& deltaTime){
	
	
	if(shape.getFillColor().a != 128) shape.setFillColor(sf::Color(255, 255, 255, 128));
	
	else shape.setFillColor(sf::Color(255, 255, 255, 255));
}

bool BonusBrick::beingHitByPlayable(const sf::FloatRect& bounds, sf::Vector2f& position, std::vector<Observer*>& observers){
	
	sf::FloatRect m_bounds = this->shape.getGlobalBounds();

	if (bounds.intersects(m_bounds)) {

		if (bounds.top >= m_bounds.top + m_bounds.height - 5.f) {
			for (Observer* observer : observers) {
				observer->hitBonusBrick(sf::Vector2f(this->position.x,this->baseGround + this->shape.getSize().y), type);
			}
			
			this->die();
		}

		return true;
	}

	return false;

	//observer to notify game to add items and new base brick, delete this bonus brick
}




