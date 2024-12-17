#include "GoodBullet.h"
#include "AssetManager.h"
#include "AutomaticStrategy.h"
#include "NonPlayableCharacter.h"

GoodBullet::GoodBullet(){
	this->m_Vx = 1.f;

	std::pair<sf::Texture*, std::vector<sf::IntRect>> image = AssetManager::getInstance()->getBonusAnimation(BonusAnimation::main_fire);

	AnimationStrategy* strategy = new AutomaticStrategy(image.first, image.second, 1.0 / 60);

	this->m_shape.setSize(sf::Vector2f((float)image.second[0].getSize().x,(float) image.second[0].getSize().y));

	this->m_animation.addStrategy(strategy);
}

void GoodBullet::collect(Item* item, const std::vector<Observer*>& observers){
}

void GoodBullet::hit(Block* block, const std::vector<Observer*>& observers){}

bool GoodBullet::canBeDeletedWhenOutOfView() const
{
	return true;
}

void GoodBullet::hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers) {
	sf::Vector2f newPosition;
	bool left = character->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition);
	bool right = character->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition);
	bool bottom = character->beingHitFromBottom(this->m_shape.getGlobalBounds(), newPosition);

	if(left == true || right == true || bottom == true) {
		character->die(observers);
	}
}

bool GoodBullet::canBeKilledByNonPlayable()
{
	return false;
}

void GoodBullet::setCenterForView(sf::View& view, sf::RenderWindow* window){}

void GoodBullet::move(const float& deltaTime){
	this->m_position.x += this->m_Vx;

	this->m_animation.changeAutomatically(deltaTime, this->m_sprite);
}

void GoodBullet::update(const float& deltaTime, const std::vector<Observer*>& observers){
	this->move(deltaTime);

	this->m_sprite.setPosition(this->m_position);
	this->m_shape.setPosition(this->m_position);
}

bool GoodBullet::findMinForView(float& minX){
	return false;
}

void GoodBullet::standInsideView(sf::View& view) {}

void GoodBullet::changeDirection(){
	this->m_Vx *= -1;
}

bool GoodBullet::canViewFollow() const
{
	return false;
}


