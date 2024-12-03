#pragma once

#include "NonPlayableCharacter.h"

class KoopaTroopa : public NonPlayableCharacter{
private:
	bool inShell;
	bool canMoveInShell;

public:
	KoopaTroopa();

	void move(const float& deltaTime) override;
	void die() override;
	
	void beingHitByPlayable(const sf::FloatRect& bounds, bool& alive);
	bool beingHitByNonPlayable(const sf::FloatRect& bounds, float& o_speed, bool& alive) override;
};

