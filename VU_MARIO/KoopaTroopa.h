#pragma once

#include "NonPlayableCharacter.h"

class Observer;

class KoopaTroopa : public NonPlayableCharacter{
private:
	bool m_inShell;
	bool m_canMoveInShell;
	float m_delay_move_time;
	
public:
	KoopaTroopa(const int& mapNum);

	void move(const float& deltaTime) override;
	void die(const std::vector<Observer*>& observers) override;
	
	void specificResultAfterBeingHitByPlayable(const std::vector<Observer*>& observers, PlayableCharacter* character) override;
	virtual void specificResultAfterBeingStoodOnByPlayable(const std::vector<Observer*>& observers, PlayableCharacter* character) override;
	void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers) override;
	bool canKillPlayable(const sf::FloatRect& bounds) override;
	virtual bool canKillNonPlayable(const sf::FloatRect& bounds) override;
};

