#pragma once

#include "Block.h"

class Stick : public Block{
public:
	Stick();
	~Stick();
	
	void specificResultAfterBeingHitFromLeft(const std::vector<Observer*>& observers) override;
	void specificResultAfterBeingHitFromRight(const std::vector<Observer*>& observers) override;
	
};

