#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <vector>

class AssetManager;
class Block;
class Item;
class AnimationStrategy;
class Observer;

class Character{

protected:
	float Vx;
	float Vy;
	bool alive;
	
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::RectangleShape shape;

	float baseGround;
	Animation animation;

	void initVariables(sf::Vector2f position, std::vector<AnimationStrategy*> animationStrategy, std::pair<sf::Texture*, std::vector<sf::IntRect>> images);

public:

	Character();

	~Character();

	virtual void move(const float& deltaTime) = 0;
	virtual void die();
	virtual void reset();
	virtual bool isDead();
	virtual void update(const float& deltaTime, std::vector<Observer*>& observers);
	virtual void draw(sf::RenderWindow* window);


	virtual void StandOn(Block* block, std::vector<Observer*>& observers);
};

