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
	this->m_animation_frame = 0.1;

	std::pair<sf::Texture*, std::vector<sf::IntRect>> images = AssetManager::getInstance()->getBonusAnimation(BonusAnimation::bonus_brick_animation);

	AnimationStrategy* newStrategy = new AutomaticStrategy(images.first,images.second,1.0 / 60);
	
	this->m_animation.addStrategy(newStrategy);
}

BonusBrick::~BonusBrick(){}

void BonusBrick::twinkle(const float& deltaTime){
	m_animation.changeAutomatically(deltaTime,this->m_sprite);
}
	
void BonusBrick::specificResultAfterBeingHitFromBottom(const std::vector<Observer*>& observers, const PlayableCharacter& character) {
	for (Observer* observer : observers) {
		observer->hitBonusBrick(sf::Vector2f(this->m_position.x, this->m_baseGround + this->m_shape.getSize().y), type);
	}

	this->die();
}

void BonusBrick::draw(sf::RenderWindow* window){
	window->draw(this->m_sprite);
}



