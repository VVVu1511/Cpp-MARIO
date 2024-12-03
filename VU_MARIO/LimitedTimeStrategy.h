#pragma once
#include "AnimationStrategy.h"

class LimitedTimeStrategy : public AnimationStrategy{
public:

	LimitedTimeStrategy();
	LimitedTimeStrategy(sf::Texture* texture, std::vector<sf::IntRect> frames, const float& SPF);
	LimitedTimeStrategy(const LimitedTimeStrategy& other);

	void die(const float& deltaTime, sf::Sprite& sprite) override;
	

	~LimitedTimeStrategy();
};

