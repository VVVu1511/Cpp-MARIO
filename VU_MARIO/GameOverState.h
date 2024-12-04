#pragma once

#include "GameState.h"

class GameOverState : public GameState{
private:
	sf::Text text;
public:
	GameOverState();
	~GameOverState();
	virtual void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font);
	virtual bool isActive();
};

