#pragma once
#include "NonPlayableCharacter.h"

class Boss : public NonPlayableCharacter{
private:
	float m_shooting_delay_time;
public:
	Boss();
	void shoot(const float& deltaTime, const std::vector<Observer*>& observers) override;
};

