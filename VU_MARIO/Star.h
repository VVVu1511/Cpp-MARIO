#pragma once
#include "Item.h"

class Observer;

class Star : public Item{
private:
	float m_jump_time = 0;
public:
	Star();
	void beingCollectedByPlayable(PlayableCharacter* character,const std::vector<Observer*>& observers) override;
	void move(const float& deltaTime) override;
	
};

