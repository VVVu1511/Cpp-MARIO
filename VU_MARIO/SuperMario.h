#pragma once
#include "Mario.h"

class SuperMario : public Mario{
public:
	virtual void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers) override;
};

