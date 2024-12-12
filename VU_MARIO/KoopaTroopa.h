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
	
	void specificResultAfterBeingHit(const std::vector<Observer*>& observers, const sf::FloatRect& bounds) override;
	void specificResultAfterBeingStoodOn(const std::vector<Observer*>& observers, const sf::FloatRect& bounds) override;
	void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers) override;
	bool canKillPlayable(const sf::FloatRect& bounds) override;
	virtual bool canKillNonPlayable(const sf::FloatRect& bounds) override;
};

