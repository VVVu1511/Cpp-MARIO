#pragma once
#include "Observer.h"
#include <vector>

class PlayingState;

class PlayingStateObserver : public Observer{
private:
	std::vector<PlayingState*>GameStates;

public:
	PlayingStateObserver();
	void addPlayableCharacter(PlayableCharacter* character) override;
	void addPlayingState(PlayingState* gamestate) override;
	void killEnemies() override;
	void collectCoins() override;
	void collectFlower() override;
	void collectGoodMushroom() override;
	void collectStar() override;
	void hitBonusBrick(const sf::Vector2f& position, ItemType type) override;
	void hitStick() override;
	void bossShooting(const sf::Vector2f& position, const float& speed) override;
	void mainShooting(const sf::Vector2f& position, const float& speed) override;
};

