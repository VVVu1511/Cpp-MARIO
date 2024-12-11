#include "KoopaTroopa.h"

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

void KoopaTroopa::specificResultAfterBeingHit(const std::vector<Observer*>& observers){
	if (this->m_inShell) {
		if (!this->m_canMoveInShell) {
			sf::Vector2f newPosition;

			bool left = this->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition);
			bool right = this->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition);

			this->m_canMoveInShell = true;
			this->m_speed = (right == true) ? 5.f : -5.f;
		}
	}
}

void KoopaTroopa::specificResultAfterBeingStoodOn(const std::vector<Observer*>& observers){
	
	if (!this->m_inShell) {
		this->m_inShell = true;
	}

	else {
		this->die();
	}
}

bool KoopaTroopa::canKill(){
	if (this->m_inShell && !this->m_canMoveInShell) return false;

	return true;
}







