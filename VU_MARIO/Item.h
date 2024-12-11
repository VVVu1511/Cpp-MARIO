#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "WorldObject.h"

enum class ItemType;
class AssetManager;
class Block;
class Observer;
class View;

class Item : public WorldObject{
protected:
	float m_Vx;
public:
	Item();

	~Item();
	
	static Item* createItem(const ItemType &type,const sf::Vector2f &position);

	virtual void move(const float& deltaTime);
	virtual void die();
	virtual void reset();
	virtual void changeDirection();

	virtual bool isDead();
	virtual void update(const float& deltaTime, const std::vector<Observer*>& observers);
	virtual void draw(sf::RenderWindow* window);
	virtual void twinkle(const float& deltaTime);
	virtual bool standInView(View view);

	virtual void hit(Block* block);
	virtual void beingCollectedByPlayable(const std::vector<Observer*>& observers);
	virtual void standOn(Block* block,const std::vector<Observer*>& observers);
};
