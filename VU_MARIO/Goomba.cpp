#include "Goomba.h"
#include "AssetManager.h"
#include "AutomaticStrategy.h"
#include "LimitedTimeStrategy.h"

Goomba::Goomba(){
	std::pair<sf::Texture*, std::vector<sf::IntRect>> image;

	image = AssetManager::getInstance()->getNonPlayableCharacter(NonPlayableCharacterType::goomba);

	AnimationStrategy* strategy = new AutomaticStrategy(image.first, image.second, 1.0 / 60);
	AnimationStrategy* strategy2 = new LimitedTimeStrategy(image.first, image.second, 1.0 / 60);

	this->m_animation.addStrategy(strategy);
	this->m_animation.addStrategy(strategy2);
	
	sf::Vector2f size((float)image.second[0].width, (float)image.second[0].height);

	this->setSize(size);

}

void Goomba::die(const std::vector<Observer*>& observers){
	
	this->m_shape.setSize(sf::Vector2f(this->m_shape.getSize().x, 16.f));

	NonPlayableCharacter::die(observers);
}
