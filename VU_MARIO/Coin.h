#pragma once
#include "Item.h"

class Observer;

class Coin : public Item{
public:
	Coin();
	
	bool beingCollectedByPlayable(const sf::FloatRect& bounds, std::vector<Observer*>& observers);
};

