#pragma once
#include "Character.h"

enum class PlayableCharacterType;
class NonPlayableCharacter;
class Block;
class Item;
class Observer;

class PlayableCharacter : public Character{

protected:

public:
	static PlayableCharacter* createCharacter(const PlayableCharacterType &type,const sf::Vector2f position);
	
	void setCenterForView(sf::View& view);
	void move(const float& deltaTime) override;
	void update(const float& deltaTime, const std::vector<Observer*>& observers) override;
	void die() override;
	virtual void reset() override;
	virtual void shoot (const float& deltaTime);
	virtual bool findMinForView(float& minX);
	virtual void standInsideView(sf::View& view);
	virtual void collectGoodMushroom();
	virtual	void collectStar();
	virtual void collectFlower();
	
	virtual bool canDestroyBrick() const;

	virtual void collect(Item* item, const std::vector<Observer*>& observers);
	virtual void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers);
	virtual void standOn(NonPlayableCharacter* character, const std::vector<Observer*>& observers);
	virtual void hit(Block* block, const std::vector<Observer*>& observers);
	void StandOn(Block* block, const std::vector<Observer*>& observers) override;
};

