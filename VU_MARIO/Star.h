#pragma once
#include "Item.h"

class Observer;

class Star : public Item{
public:
	Star();
	bool beingCollectedByPlayable(const sf::FloatRect& bounds, std::vector<Observer*>& observers);
};

