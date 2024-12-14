#pragma once
#include "NonPlayableCharacter.h"

class Bullet : public NonPlayableCharacter{
private:
	void move();
public:
	Bullet();
	void direction(const float& speed);
	bool canKillPlayable(const sf::FloatRect& bounds) override;
	void update(const float& deltaTime, const std::vector<Observer*>& observers) override;
	void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers) override;
	void hit(Block* block, const std::vector<Observer*>& observers) override;
	void specificResultAfterBeingStoodOnByPlayable(const std::vector<Observer*>& observers, PlayableCharacter* character);
	bool canBeKilledByPlayable(const sf::FloatRect& bounds) override;
};

