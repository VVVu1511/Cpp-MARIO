#pragma once
#include "Item.h"

class Observer;

class Flower : public Item{
public:
	Flower();
	void beingCollectedByPlayable(const std::vector<Observer*>& observers);
};

