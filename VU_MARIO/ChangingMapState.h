#pragma once
#include "GameState.h"
#include <iomanip>
#include <sstream>
#include <string>	


class ChangingMapState : public GameState{
private:
	std::vector<sf::Sprite>m_icons;
	std::vector<sf::Text>m_texts;
	std::vector<std::string>m_contents;

	int m_cur_score;
	int m_cur_coin;
	int m_cur_mapNum;
	int m_cur_lives;
	PlayableCharacterType m_cur_main;

public:
	ChangingMapState();
	ChangingMapState(PlayableCharacterType main, const sf::Font& font,const int& score, const int& coins, const int& mapNum, const int& time, const int& lives);
	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font) ;
	bool isActive() ;
	void drawState(sf::RenderWindow* window) ;
	void handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window) override ;
	GameState* nextState();
};

