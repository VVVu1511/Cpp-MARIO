#include "KoopaTroopa.h"
#include<iostream>
#include "PlayableCharacter.h"
#include "AssetManager.h"
#include "AutomaticStrategy.h"
#include "LimitedTimeStrategy.h"

KoopaTroopa::KoopaTroopa(const int &mapNum){
	this->m_inShell = false;
	this->m_canMoveInShell = false;
	std::pair<sf::Texture*, std::vector<sf::IntRect>> image;

	if (mapNum == 2) image = AssetManager::getInstance()->getBonusAnimation(BonusAnimation::blue_turtle);
	else if (mapNum == 3) image = AssetManager::getInstance()->getBonusAnimation(BonusAnimation::red_turtle);
	else image = AssetManager::getInstance()->getNonPlayableCharacter(NonPlayableCharacterType::koopatroopa);

	
	AnimationStrategy* strategy = new AutomaticStrategy(image.first, image.second, 1.0 / 60);
	AnimationStrategy* strategy2 = new LimitedTimeStrategy(image.first, image.second, 1.0 / 60);

	this->m_animation.addStrategy(strategy);
	sf::Vector2f size((float)image.second[0].width, (float)image.second[0].height);

	this->setSize(size);
	this->m_animation.addStrategy(strategy2);
}

void KoopaTroopa::move(const float& deltaTime){
	if (!this->m_inShell) {
		NonPlayableCharacter::move(deltaTime);
	}
	else {
		if (this->m_canMoveInShell) {
			NonPlayableCharacter::move(deltaTime);

		}

		m_animation.die(deltaTime, this->m_sprite);
	}
}

void KoopaTroopa::die(const std::vector<Observer*>& observers){
	m_animation.die(0.2,this->m_sprite);

	this->m_inShell = true;
	
	this->m_shape.setSize(this->m_sprite.getGlobalBounds().getSize());
}

void KoopaTroopa::specificResultAfterBeingHitByPlayable(const std::vector<Observer*>& observers, PlayableCharacter* character){
	if (this->m_inShell == true) {
		if (this->m_canMoveInShell == false) {
			sf::Vector2f newPosition;

			bool left = character->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition);
			bool right = character->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition);

			this->m_canMoveInShell = true;
			this->m_speed = (right == true) ? -4.f : 4.f;
		}
	}
}

void KoopaTroopa::specificResultAfterBeingStoodOnByPlayable(const std::vector<Observer*>& observers, PlayableCharacter* character){}

void KoopaTroopa::hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers){
	if (this->m_inShell == true && this->m_canMoveInShell == true) {
		sf::Vector2f newPosition;

		bool left = character->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition);
		bool right = character->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition);
		
		if (left == true || right == true) {
				character->die(observers);
		}

	}
	
	else {
		NonPlayableCharacter::hit(character, observers);
	}
}

bool KoopaTroopa::canKillNonPlayable(const sf::FloatRect& bounds){
	if (this->m_canMoveInShell == true && this->m_inShell == true) return true;

	return false;
}

bool KoopaTroopa::canKillPlayable(const sf::FloatRect& bounds){
	if (this->m_inShell == true) {
		if (this->m_canMoveInShell == false) return false;
		
		if (this->m_speed < 0 && bounds.left > this->m_position.x) return false;

		if (this->m_speed > 0 && bounds.left  < this->m_position.x) return false;
	}
	
	return true;
}







