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

public:
	ChangingMapState();
	ChangingMapState(const sf::Font& font,const int& score, const int& coins, const int& mapNum, const int& time, const int& lives);
	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font) ;
	bool isActive() ;
	GameState* nextState() ;
	void drawState(sf::RenderWindow* window) ;
	void handleInputEvent(const sf::Event*& ev, const sf::Font& font) ;
};

