#pragma once
#include<SFML/Graphics.hpp>
#include "View.h"

enum class StateOfGame {
	menu = 1,
	playing = 2,
	changingMap = 3,
	gameover = 4,
	login = 5,
};

class Observer;

class GameState{

protected:
	bool active = false;
	View view;
	bool isCreated = false;
public:
	GameState();
	virtual ~GameState() = default;
	virtual void execute(sf::RenderWindow* window,std::vector<Observer*>&observers,GameState* gameState, const float& deltaTime, const sf::Event* ev,const sf::Font& font) = 0;
	virtual bool isActive() = 0;
};

