#include "FireSequence.h"
#include "AutomaticStrategy.h"
#include "AssetManager.h"

FireSequence::FireSequence(){
	std::pair<sf::Texture*, std::vector<sf::IntRect>> image = AssetManager::getInstance()->getNonPlayableCharacter(NonPlayableCharacterType::fire_sequence);
	
	AnimationStrategy* strategy = new AutomaticStrategy(image.first,image.second,1.0 / 60);
	
	this->m_animation.addStrategy(strategy);
	sf::Vector2f size((float)image.second[0].width, (float)image.second[0].height);
	
	this->setSize(size);
}

void FireSequence::move(const float& deltaTime){
	this->m_animation.changeAutomatically(deltaTime, this->m_sprite);
	this->m_shape.rotate(1.f);
	this->m_sprite.rotate(1.f);
}

bool FireSequence::canBeKilledByPlayable(const sf::FloatRect& bounds)
{
	return false;
}

void FireSequence::update(const float& deltaTime, const std::vector<Observer*>& observers){
	this->move(deltaTime);
	this->m_sprite.setPosition(this->m_position.x + 5.f, this->m_position.y + 16.f);
	this->m_shape.setPosition(this->m_position.x + 5.f,this->m_position.y + 16.f);
}

void FireSequence::hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers){}

void FireSequence::hit(Block* block, const std::vector<Observer*>& observers){}
