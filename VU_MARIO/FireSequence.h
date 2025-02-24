#pragma once

#include "NonPlayableCharacter.h"

class FireSequence : public NonPlayableCharacter{
private:
	sf::Vector2f m_fixed_position;
	float m_rotate_speed;
public:
	FireSequence(sf::Vector2f position, const int& mapNum);
	void move(const float& deltaTime) override;
	bool canBeKilledByPlayable(const sf::FloatRect& bounds) override;
	void update(const float& deltaTime, const std::vector<Observer*>& observers) override;
	void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers) override;
	void hit(Block* block, const std::vector<Observer*>& observers) override;
};

