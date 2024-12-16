#pragma once
#include "Character.h"

enum class NonPlayableCharacterType;
class Observer;
class View;
class PlayableCharacter;

class NonPlayableCharacter : public Character{

protected:
	float m_speed = 1.f;
	virtual void setSize(const sf::Vector2f &size);
public:
	static NonPlayableCharacter* createCharacter(const NonPlayableCharacterType &type, const sf::Vector2f& position,const int& mapNum);
	
	void move(const float& deltaTime) override;
	void update(const float& deltaTime, const std::vector<Observer*>& observers) override;
	virtual void changeDirection();

	virtual void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers);
	virtual void hit(Block* block, const std::vector<Observer*>& observers);
	virtual void specificResultAfterBeingHitByPlayable(const std::vector<Observer*>& observers,PlayableCharacter* character);
	virtual void specificResultAfterBeingStoodOnByPlayable(const std::vector<Observer*>& observers, PlayableCharacter* character);
	virtual bool canKillPlayable(const sf::FloatRect& bounds);
	virtual bool canKillNonPlayable(const sf::FloatRect& bounds);
	virtual bool canBeKilledByPlayable(const sf::FloatRect& bounds);
	virtual void shoot(const float& deltaTime, const std::vector<Observer*>& observers);
	
};

