#pragma once
#include "PlayableCharacter.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Mario : public PlayableCharacter{

public:
	Mario();
	void turnToSmall() override;
	void collectGoodMushroom();
	void collectStar();
	void collectFlower();
};

