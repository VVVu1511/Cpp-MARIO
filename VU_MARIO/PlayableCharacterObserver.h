#pragma once
#include <vector>
#include "Observer.h"

class PlayableCharacter;
class PlayingState;
enum class ItemType;

class PlayableCharacterObserver : public Observer{

private:
	std::vector<PlayableCharacter*>characters;

public:
	PlayableCharacterObserver();
	void addPlayingState(PlayingState* gamestate);
	void addPlayableCharacter(PlayableCharacter* character);
	void killEnemies();
	void collectCoins();
	void collectFlower();
	void collectGoodMushroom();
	void collectStar();
	void hitBonusBrick(const sf::Vector2f &position,ItemType type);
	void hitStick();
};

