#pragma once
#include "Mario.h"

class BigMario : public Mario{
private:
	void turnToSmall();
public:
	void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers) override;
	bool canDestroyBrick() const override;
};

