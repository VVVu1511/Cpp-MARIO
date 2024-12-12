#pragma once

#include "GameState.h"

class GameOverState : public GameState{
private:
	sf::Text text;
	bool isCreated = false;
	float expiredTime = 2;
public:
	GameOverState();
	~GameOverState();
	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font) override;
	bool isActive() override;
	StateOfGame nextState() override;
};

