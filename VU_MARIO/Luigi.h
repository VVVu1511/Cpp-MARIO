#pragma once
#include "PlayableCharacter.h"


class Luigi : public PlayableCharacter{

public:
	Luigi();
	void turnToSmall() override;
	void move();
	void collectGoodMushroom();
	void collectStar();
	void collectFlower();
};

