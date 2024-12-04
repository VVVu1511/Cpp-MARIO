#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>

class MenuState : public GameState{
	//Get asset from AssetManager and draw
	//allow mouse input, choosing level, choosing character (Luigi,Mario)
private:
	
public:
	MenuState();
	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font) override;
	bool isActive() override;
};

