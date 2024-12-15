#include "Cactus.h"
#include "PlayableCharacter.h"
#include "AssetManager.h"
#include "AutomaticStrategy.h"

Cactus::Cactus(const sf::Vector2f &position){
	this->m_moving_time = 1.0;
	this->m_middle_pos = 0;
	
	this->m_moveUp = false;
	this->m_reset_position = false;

	std::pair<sf::Texture*, std::vector<sf::IntRect>> image;

	image = AssetManager::getInstance()->getNonPlayableCharacter(NonPlayableCharacterType::cactus);
	
	AnimationStrategy* strategy = new AutomaticStrategy(image.first, image.second, 1.0 / 60);
	
	this->m_animation.addStrategy(strategy);
	sf::Vector2f size((float)image.second[0].width, (float)image.second[0].height);

	this->setSize(size);

}

void Cactus::move(const float& deltaTime){
	if (this->m_position.y <= this->m_top) {
		this->m_moveUp = false;
	}

	else if (this->m_position.y >= this->m_baseGround) {
		this->m_moveUp = true;
	}

	this->m_position.y += (this->m_moveUp == true) ? -1.f : 1.f;
	
	this->m_animation.changeAutomatically(deltaTime,this->m_sprite);
}

bool Cactus::canBeKilledByPlayable(const sf::FloatRect& bounds)
{
	return false;
}

void Cactus::specificResultAfterBeingStoodOnByPlayable(const std::vector<Observer*>& observers, PlayableCharacter* character){
	character->die(observers);
}

void Cactus::update(const float& deltaTime, const std::vector<Observer*>& observers){
	
	if (this->m_reset_position == false) {
		this->m_reset_position = true;
		this->m_top = this->m_position.y - 35.f;
		this->m_baseGround = this->m_position.y + this->m_shape.getSize().y - 20.f;
		this->m_middle_pos = this->m_top + 35.f;
	}

	this->move(deltaTime);

	this->m_animation.changeAutomatically(deltaTime, this->m_sprite);
	this->m_shape.setPosition(this->m_position.x + 10.f,this->m_position.y);
	this->m_sprite.setPosition(this->m_position.x + 10.f,this->m_position.y);

	if (this->m_position.y <= this->m_middle_pos) {
		sf::IntRect curRect = this->m_sprite.getTextureRect();
		this->m_sprite.setTextureRect(sf::IntRect(curRect.left,curRect.top,curRect.width,this->m_middle_pos - this->m_position.y));
	}
	else {
		this->m_sprite.setTextureRect(sf::IntRect(0,0,0,0));
	}
}

void Cactus::hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers)
{
}

void Cactus::hit(Block* block, const std::vector<Observer*>& observers)
{
}

void Cactus::reset(){}

void Cactus::StandOn(Block* block, const std::vector<Observer*>& observers){}

