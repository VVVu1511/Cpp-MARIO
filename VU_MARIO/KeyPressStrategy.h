#pragma once
#include "AnimationStrategy.h"


class KeyPressStrategy : public AnimationStrategy{
private:
	int startOfMoving;
	int bound;
	
public:
	KeyPressStrategy();
	KeyPressStrategy(sf::Texture* texture, std::vector<sf::IntRect> frames, const float& SPF);
	KeyPressStrategy(const KeyPressStrategy& other);

	void moveleft(const float& deltaTime, sf::Sprite& sprite) override;
	void moveright(const float& deltaTime, sf::Sprite& sprite) override;
	void jump(const float& deltaTime, sf::Sprite& sprite) override;
	
	~KeyPressStrategy();
};

