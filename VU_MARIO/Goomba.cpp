#include "Goomba.h"
#include "AssetManager.h"
#include "AutomaticStrategy.h"
#include "LimitedTimeStrategy.h"

Goomba::Goomba(const int& mapNum){
	std::pair<sf::Texture*, std::vector<sf::IntRect>> image;

	if (mapNum == 1) image = AssetManager::getInstance()->getNonPlayableCharacter(NonPlayableCharacterType::goomba);
	else if (mapNum == 2) image = AssetManager::getInstance()->getBonusAnimation(BonusAnimation::winter_goomba);

	AnimationStrategy* strategy = new AutomaticStrategy(image.first, image.second, 1.0 / 60);
	AnimationStrategy* strategy2 = new LimitedTimeStrategy(image.first, image.second, 1.0 / 60);

	this->m_animation.addStrategy(strategy);
	this->m_animation.addStrategy(strategy2);
	
	sf::Vector2f size((float)image.second[0].width, (float)image.second[0].height);

	this->setSize(size);

}

void Goomba::die(const std::vector<Observer*>& observers){
	
	this->m_shape.setSize(sf::Vector2f(this->m_shape.getSize().x, 16.f));

	this->m_sprite.setScale(1, 0.5);

	NonPlayableCharacter::die(observers);
}
