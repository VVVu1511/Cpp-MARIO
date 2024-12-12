#include "BonusBrick.h"
#include "AutomaticStrategy.h"
#include "Animation.h"
#include "Observer.h"
#include "AssetManager.h"

ItemType BonusBrick::getRandomItem(){
	int randValue = rand() % 100; 

	if (randValue > 95) {
		return ItemType::star; 
	}
	else if (randValue > 90) {
		return ItemType::flower; 
	}
	else if (randValue > 85) {
		return ItemType::mushroom; 
	}
	
	return ItemType::coin; 
}

BonusBrick::BonusBrick(){
	this->type = getRandomItem();
}

BonusBrick::~BonusBrick(){}


void BonusBrick::twinkle(const float& deltaTime){
	if(m_shape.getFillColor().a != 128) m_shape.setFillColor(sf::Color(255, 255, 255, 128));
	
	else m_shape.setFillColor(sf::Color(255, 255, 255, 255));
}

void BonusBrick::specificResultAfterBeingHitFromBottom(const std::vector<Observer*>& observers){
	for (Observer* observer : observers) {
		observer->hitBonusBrick(sf::Vector2f(this->m_position.x, this->m_baseGround + this->m_shape.getSize().y), type);
	}

	this->die();
}



