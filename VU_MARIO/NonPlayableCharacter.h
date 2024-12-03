#pragma once
#include "Character.h"

enum class NonPlayableCharacterType;
class Observer;
class View;

class NonPlayableCharacter : public Character{

protected:
	
	float speed = 0.5f;

public:
	static NonPlayableCharacter* createCharacter(NonPlayableCharacterType type, sf::Vector2f position);
	
	void move(const float& deltaTime) override;
	void update(const float& deltaTime, std::vector<Observer*>& observers) override;
	virtual bool standInView(View view);

	virtual void hit(NonPlayableCharacter* character, std::vector<Observer*>& observers);
	virtual void hit(Block* block, std::vector<Observer*>& observers);
	
	virtual bool beingHitByNonPlayable(const sf::FloatRect& bounds, float& o_speed, bool& alive);
	virtual bool beingStoodOnByPlayable(const sf::FloatRect& bounds, std::vector<Observer*>& observers);
	virtual void beingHitByPlayable(const sf::FloatRect& bounds,bool &alive);
	virtual void beingHitByBlock(const sf::FloatRect& bounds, std::vector<Observer*>& observers);
};

