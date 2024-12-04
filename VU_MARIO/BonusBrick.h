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
	
	bool beingHitByPlayable(const sf::FloatRect& bounds, sf::Vector2f& position, std::vector<Observer*>& observers);

};