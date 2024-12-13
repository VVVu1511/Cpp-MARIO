#pragma once

#include "NonPlayableCharacter.h"

class Observer;

class KoopaTroopa : public NonPlayableCharacter{
private:
	bool m_inShell;
	bool m_canMoveInShell;
	
public:
	KoopaTroopa();

	void move(const float& deltaTime) override;
	void die() override;
	
	void specificResultAfterBeingHitByPlayable(const std::vector<Observer*>& observers, const PlayableCharacter& character) override;
	void specificResultAfterBeingStoodOnByPlayable(const std::vector<Observer*>& observers, const PlayableCharacter& character) override;
	void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers) override;
	bool canKillPlayable(const sf::FloatRect& bounds) override;
	virtual bool canKillNonPlayable(const sf::FloatRect& bounds) override;
};

