#pragma once
#include "Item.h"

class Observer;

class Flower : public Item{
public:
	Flower();
	bool beingCollectedByPlayable(const sf::FloatRect& bounds, std::vector<Observer*>& observers);
};

