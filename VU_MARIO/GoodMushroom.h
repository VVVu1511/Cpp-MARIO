#pragma once
#include "Item.h"

class Observer;

class GoodMushroom : public Item{
public:
	GoodMushroom();
	void beingCollectedByPlayable(const std::vector<Observer*>& observers);
};

