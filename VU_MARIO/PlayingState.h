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
	bool m_restart_called = false;
	bool m_congrat_called = false;
	bool m_changing_called = false;

	int coin = 0;
	int lives = 2;
	int mapNum;
	float time = 400.f;
	
	int score = 0;
	PlayableCharacterType m_mainCharacterType;

	std::vector<PlayableCharacter*>all_playable_characters;
	std::vector<PlayableCharacter*>garbage_of_playable_characters;
	
	std::vector<NonPlayableCharacter*>all_non_playable_characters;
	std::vector<NonPlayableCharacter*>garbage_of_non_playable_characters;
	
	std::vector<Block*>all_blocks;
	std::vector<Block*>garbage_of_all_blocks;


	std::vector<Item*>all_items;
	std::vector<Item*>garbage_of_all_items;

	std::vector<sf::Text>m_attributes_text;
	
	Collision collision;
	
	void createMap(sf::RenderWindow* window, std::vector<Observer*>& observers, PlayingState* gameState);
	void update(sf::RenderWindow* window, std::vector<Observer*>& observers, const float& deltaTime);
	void drawMap(sf::RenderWindow* window, const sf::Font& font);
	void temporaryCleanUp(sf::RenderWindow* window, const sf::Font& font);
	void ultimateCleanUp();
	void cleanObserverForEachLive(std::vector<Observer*>& observers);
	void drawAttributes(sf::RenderWindow* window,const sf::Font& font);
	

	void RealExecute(sf::RenderWindow* window, std::vector<Observer*>& observers, PlayingState* gameState, const float& deltaTime, const sf::Font& font);
public:
	PlayingState();
	PlayingState(const std::pair<int, PlayableCharacterType>& mapAndMainCharacter);
	PlayingState(const int &coin, const int& live, const int& mapNum, const int& score,const PlayableCharacterType main);
	~PlayingState();
	
	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font);
	void addCoin();
	void addScore(int score);
	void decreaseLives(sf::RenderWindow* window, const sf::Font& font);
	void changeMap();
	void restart();
	bool isActive() override;
	void hitBonusBrick(const sf::Vector2f& position, ItemType type);
	GameState* nextState() override;
	void drawState(sf::RenderWindow* window) override;
	void handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window) override;

	void bossShootingEvent(const sf::Vector2f& position, const float& speed);
	void mainShootingEvent(const sf::Vector2f& position, const float& speed);
	void mainCollectingFlowerEvent(PlayableCharacter* character);
	void mainCollectingMushroomEvent(PlayableCharacter* character);
	void mainCollectingStarEvent(PlayableCharacter* character);
	void mainBecomeSmall(PlayableCharacter* character);
};

