#include "Bullet.h"
#include "AssetManager.h"
#include "AutomaticStrategy.h"
#include "PlayableCharacter.h"

void Bullet::move(){
	this->m_position.x += this->m_speed;
}

Bullet::Bullet(){
	this->m_speed = 0.5f;

	std::pair<sf::Texture*, std::vector<sf::IntRect>> image;

	image = AssetManager::getInstance()->getBonusAnimation(BonusAnimation::boss_fire);

	AnimationStrategy* strategy = new AutomaticStrategy(image.first, image.second, 1.0 / 60);

	this->m_animation.addStrategy(strategy);
}

bool Bullet::canKillPlayable(const sf::FloatRect& bounds){
	return true;
}

void Bullet::update(const float& deltaTime, const std::vector<Observer*>& observers){
	NonPlayableCharacter::move(deltaTime);

	this->m_animation.changeAutomatically(deltaTime, this->m_sprite);

	this->m_sprite.setPosition(this->m_position);
	this->m_shape.setPosition(this->m_position);
}

void Bullet::hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers)
{
}

//void Bullet::hit(Block* block, const std::vector<Observer*>& observers)
//{
//}

void Bullet::specificResultAfterBeingStoodOnByPlayable(const std::vector<Observer*>& observers, PlayableCharacter* character){
	character->die(observers);
}

bool Bullet::canBeKilledByPlayable(const sf::FloatRect& bounds)
{
	return false;
}

void Bullet::direction(const float& speed){
	if (speed < 0) this->m_speed *= (-1);
}




