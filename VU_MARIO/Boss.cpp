#include "Boss.h"
#include "AssetManager.h"
#include "AutomaticStrategy.h"
#include "Observer.h"

Boss::Boss(){
	this->m_shooting_delay_time = 0.f;

	std::pair<sf::Texture*, std::vector<sf::IntRect>> image;

	image = AssetManager::getInstance()->getNonPlayableCharacter(NonPlayableCharacterType::boss);

	AnimationStrategy* strategy = new AutomaticStrategy(image.first, image.second, 1.0 / 60);

	this->m_animation.addStrategy(strategy);

	sf::Vector2f size((float)image.second[0].width, (float)image.second[0].height);

	this->setSize(size);
}

void Boss::shoot(const float& deltaTime, const std::vector<Observer*>& observers){
	if (this->m_shooting_delay_time > 0.f) {
		this->m_shooting_delay_time -= deltaTime;
		return;
	}

	this->m_shooting_delay_time = 0.5f;

	for (Observer* observer : observers) {
		observer->bossShooting(this->m_position,this->m_speed);
	}
}
