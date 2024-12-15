#pragma once
#include "Item.h"

class Observer;

class Coin : public Item{
public:
	Coin();
	
	void beingCollectedByPlayable(PlayableCharacter* character,const std::vector<Observer*>& observers) override;
	void move(const float& deltaTime) override;
	void standOn(Block* block, const std::vector<Observer*>& observers) override;
	void reset() override;
};

