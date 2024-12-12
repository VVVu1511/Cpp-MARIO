#include "KoopaTroopa.h"
#include<iostream>

KoopaTroopa::KoopaTroopa(){
	this->m_inShell = false;
	this->m_canMoveInShell = false;
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

void KoopaTroopa::die(){
	m_animation.die(0.2,this->m_sprite);

	this->m_inShell = true;
	
	this->m_shape.setSize(this->m_sprite.getGlobalBounds().getSize());
}

void KoopaTroopa::specificResultAfterBeingHit(const std::vector<Observer*>& observers, const sf::FloatRect& bounds){
	if (this->m_inShell == true) {
		if (this->m_canMoveInShell == false) {
			sf::Vector2f newPosition;

			bool left = this->beingHitFromLeftBy(bounds, newPosition);
			bool right = this->beingHitFromRightBy(bounds, newPosition);

			this->m_canMoveInShell = true;
			this->m_speed = (right == true) ? -4.f : 4.f;
		}
	}
}

void KoopaTroopa::specificResultAfterBeingStoodOn(const std::vector<Observer*>& observers, const sf::FloatRect& bounds){
	
}

void KoopaTroopa::hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers){
	if (this->m_inShell == true && this->m_canMoveInShell == true) {
		sf::Vector2f newPosition;

		bool left = character->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition);
		bool right = character->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition);
		
		if (left == true || right == true) {
				character->die();
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







