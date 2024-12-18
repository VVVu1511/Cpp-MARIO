#pragma once
#include "NonPlayableCharacter.h"

class Goomba : public NonPlayableCharacter{
public:
	Goomba(const int& mapNum);
	void die(const std::vector<Observer*>& observers) override;
};

