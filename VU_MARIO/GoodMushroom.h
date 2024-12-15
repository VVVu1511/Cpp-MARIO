#pragma once
#include "Item.h"

class Observer;

class GoodMushroom : public Item{
public:
	GoodMushroom();
	void beingCollectedByPlayable(PlayableCharacter* character,const std::vector<Observer*>& observers);
};

