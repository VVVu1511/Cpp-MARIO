#pragma once
#include "GameState.h"

class CongratulationState : public GameState{
private:
	sf::Text text;
public:
	CongratulationState();
	CongratulationState(sf::RenderWindow* window);

	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font) override;
	bool isActive() override;
	void drawState(sf::RenderWindow* window) override;
	void handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window) override;
};

