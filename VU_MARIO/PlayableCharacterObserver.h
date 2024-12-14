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
	void addPlayingState(PlayingState* gamestate) override;
	void addPlayableCharacter(PlayableCharacter* character) override;
	void killEnemies() override;
	void collectCoins() override;
	void collectFlower() override;
	void collectGoodMushroom() override;
	void collectStar() override;
	void hitBonusBrick(const sf::Vector2f &position,ItemType type) override;
	void hitStick() override;
	void bossShooting(const sf::Vector2f& position, const float& speed) override;
	void mainShooting(const sf::Vector2f& position, const float& speed);
};

