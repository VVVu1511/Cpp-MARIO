#pragma once
#include "GameState.h"
#include "PlayingStateObserver.h"
#include "Collision.h"
#include "PlayableCharacter.h"
#include "NonPlayableCharacter.h"
#include "Block.h"
#include "Item.h"
#include<random>


class Observer;
class PlayingState;
class Observer;
enum class UpdateType;


class PlayingState : public GameState{
private:
	
	int coin = 0;
	int lives = 2;
	int mapNum = 1;
	float time = 400;
	int score = 0;
	

	std::vector<PlayableCharacter*>all_playable_characters;
	std::vector<NonPlayableCharacter*>all_non_playable_characters;
	std::vector<Block*>all_blocks;
	std::vector<Item*>all_items;
	
	Collision collision;
	bool isMapCreated = false;
	
	
	void createMap(sf::RenderWindow* window, std::vector<Observer*>& observers, PlayingState* gameState);
	void update(sf::RenderWindow* window, std::vector<Observer*>& observers, const float& deltaTime);
	void drawMap(sf::RenderWindow* window, const sf::Font& font);
	void temporaryCleanUp();
	void ultimateCleanUp();
	void cleanObserverForEachLive(std::vector<Observer*>& observers);
	void drawAttributes(sf::RenderWindow* window,const sf::Font& font);

	void RealExecute(sf::RenderWindow* window, std::vector<Observer*>& observers, PlayingState* gameState, const float& deltaTime, const sf::Font& font);
public:
	PlayingState();
	~PlayingState();
	
	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font);
	void addCoin();
	void addScore(int score);
	void decreaseLives();
	void changeMap();
	void restart();
	bool isActive() override;
	void hitBonusBrick(const sf::Vector2f& position, ItemType type);
};

