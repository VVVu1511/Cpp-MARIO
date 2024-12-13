#pragma once
#include "Mario.h"

class FireMario : public Mario{
private:
	float m_time_shoot;
	void setTimeShoot();
	void setTimeAlive();
public:
	FireMario();
	void shoot(const float& deltaTime) override;
	void update(const float& deltaTime, const std::vector<Observer*>& observers) override;
};

