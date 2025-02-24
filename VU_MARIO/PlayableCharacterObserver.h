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
	void collectFlower(PlayableCharacter* character) override;
	void collectGoodMushroom(PlayableCharacter* character) override;
	void collectStar(PlayableCharacter* character) override;
	void hitBonusBrick(const sf::Vector2f &position,ItemType type) override;
	void hitStick() override;
	void bossShooting(const sf::Vector2f& position, const float& speed) override;
	void mainShooting(const sf::Vector2f& position, const float& speed);
	void mainTurnToSmall(PlayableCharacter* character) override;
};

