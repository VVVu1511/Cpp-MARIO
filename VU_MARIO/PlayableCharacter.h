#pragma once
#include "Character.h"

enum class PlayableCharacterType;
class NonPlayableCharacter;
class Block;
class Item;
class Observer;

class PlayableCharacter : public Character{

private:
	bool isBig;
	bool isSuper;
	bool isFire;
	// 
	bool is_spamming_W = false;
public:
	static PlayableCharacter* createCharacter(PlayableCharacterType type,sf::Vector2f position);
	
	void setCenterForView(sf::View& view);
	void move(const float& deltaTime) override;
	void update(const float& deltaTime, std::vector<Observer*>& observers) override;
	void die() override;
	virtual void reset() override;
	virtual void shoot();
	virtual bool findMinForView(float& minX);
	virtual void standInView(sf::View& view);
	virtual void collectGoodMushroom();
	virtual	void collectStar();
	virtual void collectFlower();

	

	virtual void collect(Item* item, std::vector<Observer*>& observers);
	virtual void hit(NonPlayableCharacter* character, std::vector<Observer*>& observers);
	virtual void standOn(NonPlayableCharacter* character, std::vector<Observer*>& observers);
	virtual void hit(Block* block, std::vector<Observer*>& observers);

};

