#pragma once
#include<map>
#include <SFML/Graphics.hpp>
#include "WorldObject.h"

class Animation;
class AssetManager;
class NonPlayableCharacter;
class Item;
enum class BlockType;
class Observer;
class View;
class PlayableCharacter;

class Block : public WorldObject{
protected:
	bool interact;
	void updateGravity();
	virtual bool isMidAir();

public:
	
	Block();

	~Block();

	static Block* createBlock(const BlockType &type,const sf::Vector2f& position);

	virtual void die();
	virtual bool isDead();
	virtual void draw(sf::RenderWindow* window);
	virtual void update(const float& deltaTime, const std::vector<Observer*>& observers);
	virtual void twinkle(const float& deltaTime);
	virtual bool standInView(View view);
	virtual bool canInteract();
	virtual void jump();
	virtual bool connectToUnderground();
	virtual bool connectToGround();
	virtual bool canKillPlayable();


	virtual void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers);
	virtual void hit(Item* item, const std::vector<Observer*>& observers);

	virtual void specificResultAfterBeingHitFromLeft(const std::vector<Observer*>& observers, const PlayableCharacter& character);
	virtual void specificResultAfterBeingHitFromRight(const std::vector<Observer*>& observers, const PlayableCharacter& character);
	virtual void specificResultAfterBeingHitFromBottom(const std::vector<Observer*>& observers, const PlayableCharacter& character);

};

