#pragma once

#include "Block.h"

class Stick : public Block{
public:
	Stick();
	~Stick();
	bool beingHitByPlayable(const sf::FloatRect& bounds, sf::Vector2f& position, std::vector<Observer*>& observers) override;
};

