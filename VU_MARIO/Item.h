#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"

enum class ItemType;
class AssetManager;
class Block;
class Observer;
class View;

class Item{

protected:
	bool alive = true;

	sf::Vector2f position;
	sf::Sprite sprite;
	sf::RectangleShape shape;
	
	Animation animation;
	float baseGround;

public:
	Item();

	~Item();
	
	static Item* createItem(ItemType type,sf::Vector2f position);

	virtual void move();
	virtual void die();
	virtual void reset();

	virtual bool isDead();
	virtual void update(const float& deltaTime, std::vector<Observer*>& observers);
	virtual void draw(sf::RenderWindow* window);
	virtual void twinkle(const float& deltaTime);
	virtual bool standInView(View view);


	virtual void beingHitByBlock(const sf::FloatRect& bounds, std::vector<Observer*>& observers);
	//pass bool into this
	virtual bool beingCollectedByPlayable(const sf::FloatRect& bounds, std::vector<Observer*>& observers);
	virtual void standOn(Block* block, std::vector<Observer*>& observers);

};
