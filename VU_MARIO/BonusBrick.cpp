#include "BonusBrick.h"
#include "AutomaticStrategy.h"
#include "Animation.h"
#include "Observer.h"
#include "AssetManager.h"
#include <random>
ItemType BonusBrick::getRandomItem()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 99);

	int randValue = dis(gen);
	std::cout << "Random Value: " << randValue << '\n';

	if (randValue < 50) {                  // 0-49: 50% Mushroom
		return ItemType::mushroom;
	}
	else if (randValue < 80) {             // 50-79: 30% Fire Flower
		return ItemType::flower;
	}
	else if (randValue < 90) {             // 80-89: 10% Starman
		return ItemType::star;
	}
	//else if (randValue < 95) {             // 90-94: 5% 1-Up Mushroom
	//	return ItemType::one_up_mushroom;
	//}

	return ItemType::coin;                 // 95-99: 5% Coins
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



