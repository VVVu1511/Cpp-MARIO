#pragma once
#include "PlayableCharacter.h"

class BigMario : public PlayableCharacter{
private:
	void init();
public:
	BigMario();
	BigMario(PlayableCharacter* other);
	bool canDestroyBrick() const override;
	void die(const std::vector<Observer*>& observers) override;
	void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers) override;
};

