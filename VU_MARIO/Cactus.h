#pragma once
#include "NonPlayableCharacter.h"

class Cactus : public NonPlayableCharacter{
private:
	float m_moving_time;
	float m_top;
	bool m_moveUp;
	bool m_reset_position;
	float m_middle_pos;
public:
	Cactus(const sf::Vector2f &position);

	void move(const float& deltaTime) override;
	bool canBeKilledByPlayable(const sf::FloatRect& bounds) override;
	void specificResultAfterBeingStoodOnByPlayable(const std::vector<Observer*>& observers, PlayableCharacter* character) override;
	void update(const float& deltaTime, const std::vector<Observer*>& observers) override;
	void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers) override;
	void hit(Block* block, const std::vector<Observer*>& observers) override;
	void reset() override;
	void StandOn(Block* block, const std::vector<Observer*>& observers) override;
};

