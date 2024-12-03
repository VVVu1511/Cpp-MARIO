#pragma once
#include "Observer.h"
#include <vector>

class PlayingState;

class PlayingStateObserver : public Observer{
private:
	std::vector<PlayingState*>GameStates;

public:
	PlayingStateObserver();
	void addPlayableCharacter(PlayableCharacter* character);
	void addPlayingState(PlayingState* gamestate);
	void killEnemies();
	void collectCoins();
	void collectFlower();
	void collectGoodMushroom();
	void collectStar();
	void hitBonusBrick(const sf::Vector2f& position, ItemType type);
	void hitStick();
};

