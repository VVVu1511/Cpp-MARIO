#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "WorldObject.h"
#include <vector>

class AssetManager;
class Block;
class Item;
class AnimationStrategy;
class Observer;
class View;

class Character : public WorldObject{

protected:
	float m_Vx = 5.f;
	float m_Vy;

	void initVariables(const sf::Vector2f &position, const std::vector<AnimationStrategy*>& animationStrategy,const std::pair<sf::Texture*, std::vector<sf::IntRect>>& images);
	bool isMidAir();

public:

	Character();

	~Character();

	virtual void move(const float& deltaTime) = 0;

	virtual void die(const std::vector<Observer*>& observers) ;
	virtual void reset();
	virtual bool isDead();
	virtual void update(const float& deltaTime, const std::vector<Observer*>& observers);
	virtual void draw(sf::RenderWindow* window);
	virtual bool standInView(View view);
	virtual bool canAdvanced();

	virtual void StandOn(Block* block, const std::vector<Observer*>& observers);
};

