#pragma once
#include <SFML/Graphics.hpp>

class PlayableCharacter;
class PlayingState;
enum class ItemType;

class Observer{

public:
	virtual void addPlayableCharacter(PlayableCharacter* character) = 0;
	virtual void addPlayingState(PlayingState* gamestate) = 0;
	virtual void killEnemies() = 0;
	virtual void collectCoins() = 0;
	virtual void collectFlower(PlayableCharacter* character) = 0;
	virtual void collectGoodMushroom(PlayableCharacter* character) = 0;
	virtual void collectStar(PlayableCharacter* character) = 0;
	virtual void hitBonusBrick(const sf::Vector2f& position, ItemType type) = 0;
	virtual void hitStick() = 0;
	virtual void bossShooting(const sf::Vector2f& position, const float& speed) = 0;
	virtual void mainShooting(const sf::Vector2f& position, const float& speed) = 0;
	virtual void mainTurnToSmall(PlayableCharacter* character) = 0;
};

