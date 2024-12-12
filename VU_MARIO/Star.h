#pragma once
#include "Item.h"

class Observer;

class Star : public Item{
private:
	
public:
	Star();
	void beingCollectedByPlayable(const std::vector<Observer*>& observers);
	void move(const float& deltaTime) override;
	
};

