#pragma once
#include "Block.h"
#include "Animation.h"
#include <random>

class AnimationStrategy;
enum class ItemType;
class Observer;

class BonusBrick : public Block{

private:
	ItemType type;

	ItemType getRandomItem();
public:
	BonusBrick();
	~BonusBrick();
	
	void twinkle(const float& deltaTime);
	
	void specificResultAfterBeingHitFromBottom(const std::vector<Observer*>& observers) override;
};