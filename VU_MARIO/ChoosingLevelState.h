#pragma once
#include "GameState.h"

class ChoosingLevelState : public GameState{

private:
	std::vector<sf::RectangleShape> m_all_buttons;
	std::vector<std::string> m_contents;
	std::vector<sf::Text>m_texts;	
	std::string m_Input;
	
public:
	ChoosingLevelState(sf::RenderWindow* window, const sf::Font& font);
	void drawState(sf::RenderWindow* window);
	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font) override;
	bool isActive() override;
	GameState* nextState() override;
	void handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window) override;
};

