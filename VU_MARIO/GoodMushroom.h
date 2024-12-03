#pragma once
#include "Item.h"

class Observer;

class GoodMushroom : public Item{
public:
	GoodMushroom();
	bool beingCollectedByPlayable(const sf::FloatRect& bounds, std::vector<Observer*>& observers);
};

