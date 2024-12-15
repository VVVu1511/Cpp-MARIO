#pragma once
#include "PlayableCharacter.h"


class SuperMario : public PlayableCharacter{
private:
	void init();
public:
	SuperMario();

	SuperMario(PlayableCharacter* character);
	void die(const std::vector<Observer*>& observers) override;
	bool canBeKilledByNonPlayable() override;
	void update(const float& deltaTime, const std::vector<Observer*>& observers) override;
};

