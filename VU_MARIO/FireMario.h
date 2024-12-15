#pragma once
#include "PlayableCharacter.h"

class FireMario : public PlayableCharacter{
private:
	float m_time_shoot;
	void setTimeShoot();
	void init();
	void setTimeAlive();
public:
	FireMario();
	FireMario(PlayableCharacter* character);
	void shoot(const float& deltaTime, const std::vector<Observer*>& observers) override;
	void update(const float& deltaTime, const std::vector<Observer*>& observers) override;
};

