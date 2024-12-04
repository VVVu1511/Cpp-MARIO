#pragma once
#include<map>
#include <SFML/Graphics.hpp>


class Animation;
class AssetManager;
class NonPlayableCharacter;
class Item;
enum class BlockType;
class Observer;
class View;

class Block{
protected:
	
	bool alive;
	sf::Vector2f position;
	float baseGround;
	sf::RectangleShape shape;

public:
	
	Block();

	~Block();

	static Block* createBlock(BlockType type, sf::Vector2f position);
    
	virtual void die();
	virtual bool isDead();
	virtual void draw(sf::RenderWindow* window);
	virtual void update(const float& deltaTime, std::vector<Observer*>& observers);
	virtual void twinkle(const float& deltaTime);
	virtual bool standInView(View view);

	virtual void hit(NonPlayableCharacter* character, std::vector<Observer*>& observers);
	virtual void hit(Item* item, std::vector<Observer*>& observers);


	virtual void beingStoodOnByCharacter(float& baseGround, const sf::FloatRect& bounds);
	virtual int beingHitByPlayable(const sf::FloatRect& bounds,sf::Vector2f& position, std::vector<Observer*>& observers);
	virtual bool beingHitByNonPlayable(const sf::FloatRect& bounds, sf::Vector2f& position, std::vector<Observer*>& observers, float& speed);

};

