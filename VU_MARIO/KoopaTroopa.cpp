#include "KoopaTroopa.h"

KoopaTroopa::KoopaTroopa(){
	this->inShell = false;
	this->canMoveInShell = false;
}

void KoopaTroopa::move(const float& deltaTime){
	if (!this->inShell) {
		NonPlayableCharacter::move(deltaTime);
	}
	else {
		if (this->canMoveInShell) {
			NonPlayableCharacter::move(deltaTime);

		}

		animation.die(deltaTime, this->sprite);
	}
}

void KoopaTroopa::die(){
	Character::die();

	this->alive = true;
	this->inShell = true;

}

void KoopaTroopa::beingHitByPlayable(const sf::FloatRect& bounds, bool& alive){
	if (!this->inShell) {
		NonPlayableCharacter::beingHitByPlayable(bounds, alive);
	}
	else {

		sf::FloatRect m_bounds = this->shape.getGlobalBounds();
		
		if (m_bounds.intersects(bounds)) {
			if (!this->canMoveInShell) {
				this->canMoveInShell = true;
				this->speed *= 6;
			}
			else {
				NonPlayableCharacter::beingHitByPlayable(bounds, alive);
			}
		}
	}
}

bool KoopaTroopa::beingHitByNonPlayable(const sf::FloatRect& bounds, float& o_speed, bool& alive){
	if (!this->inShell) {
		return NonPlayableCharacter::beingHitByNonPlayable(bounds, o_speed,alive);
	}
	else {
		if (!this->canMoveInShell) {
			return NonPlayableCharacter::beingHitByNonPlayable(bounds, o_speed,alive);
		}
		else {
			if (NonPlayableCharacter::beingHitByNonPlayable(bounds, o_speed,alive)) {
				
				this->speed = -this->speed;

				alive = false;

				return true;
			}
		}
	}

	return false;
}







