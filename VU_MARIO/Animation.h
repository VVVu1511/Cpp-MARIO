#pragma once
#include<SFML/Graphics.hpp>
#include "AnimationStrategy.h"

class Animation {
private:
	std::vector<AnimationStrategy*> strategies;
public:
	Animation();
	Animation(std::vector<AnimationStrategy*>animation_strategies);
	Animation(Animation& other);
	~Animation();

	void addStrategy(AnimationStrategy* animationStrategy);

	void die(const float& deltaTime, sf::Sprite& sprite);
	void moveleft(const float& deltaTime, sf::Sprite& sprite);
	void moveright(const float& deltaTime, sf::Sprite& sprite);
	void changeAutomatically(const float& deltaTime, sf::Sprite& sprite);
	void jump(const float& deltaTime, sf::Sprite& sprite);
	void doNothing(sf::Sprite& sprite);
};










