#pragma once
#include "PlayableCharacter.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Mario : public PlayableCharacter{
private:
	void init();
public:
	Mario();
	Mario(PlayableCharacter* character);
	bool canAdvanced() override;
};

