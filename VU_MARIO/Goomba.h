#pragma once
#include "NonPlayableCharacter.h"

class Goomba : public NonPlayableCharacter{
public:
	Goomba();
	void die(const std::vector<Observer*>& observers) override;
};

