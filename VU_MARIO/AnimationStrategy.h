#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

class AnimationStrategy{

protected:

	sf::Texture* texture;
	std::vector<sf::IntRect> frames;
	int frameSize;
	float SPF;
	int curFrameNum;

public:
	AnimationStrategy();
	AnimationStrategy(sf::Texture* texture, std::vector<sf::IntRect> frames,const float& SPF);
	AnimationStrategy(AnimationStrategy& other);
	~AnimationStrategy();

	virtual void die(const float& deltaTime, sf::Sprite& sprite);
	virtual void moveleft(const float& deltaTime, sf::Sprite& sprite);
	virtual void moveright(const float& deltaTime, sf::Sprite& sprite);
	virtual void changeAutomatically(const float& deltaTime, sf::Sprite& sprite);
	virtual void jump(const float& deltaTime, sf::Sprite& sprite);
	virtual void doNothing(sf::Sprite& sprite);
	virtual void setSprite(sf::Sprite& sprite);
	virtual void changeTexture(sf::Texture* texture, std::vector<sf::IntRect> frames);
};

