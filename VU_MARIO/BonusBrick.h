#pragma once
#include "Block.h"
#include "Animation.h"

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
	
	int beingHitByPlayable(const sf::FloatRect& bounds, sf::Vector2f& position, std::vector<Observer*>& observers);

};