#pragma once

#include "GameState.h"

class GameOverState : public GameState{
private:
	sf::Text text;
	
public:
	GameOverState();
	GameOverState(sf::RenderWindow* window);
	~GameOverState();
	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font) override;
	bool isActive() override;
	GameState* nextState() override;
	void handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window) override;
	void drawState(sf::RenderWindow* window) override;
};

