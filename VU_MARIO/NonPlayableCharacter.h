#pragma once
#include "Character.h"

enum class NonPlayableCharacterType;
class Observer;
class View;

class NonPlayableCharacter : public Character{
protected:
	
	float m_speed = 1.f;

public:
	static NonPlayableCharacter* createCharacter(const NonPlayableCharacterType &type, const sf::Vector2f& position);
	
	void move(const float& deltaTime) override;
	void update(const float& deltaTime, const std::vector<Observer*>& observers) override;
	virtual void changeDirection();

	virtual void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers);
	virtual void hit(Block* block, const std::vector<Observer*>& observers);
	virtual void specificResultAfterBeingHit(const std::vector<Observer*>& observers,const sf::FloatRect& bounds);
	virtual void specificResultAfterBeingStoodOn(const std::vector<Observer*>& observers, const sf::FloatRect& bounds);
	virtual bool canKillPlayable(const sf::FloatRect& bounds);
	virtual bool canKillNonPlayable(const sf::FloatRect& bounds);
};

