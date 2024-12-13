#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <vector>

class MenuState : public GameState{

private:
	static std::string m_characterInput;
	static std::string m_levelInput;

	sf::RectangleShape m_menu_frames;
	std::vector<sf::RectangleShape> m_menu_all_buttons;
	std::vector<std::string> m_menu_contents;
	std::vector<sf::Text>m_menu_texts;

	bool m_buttonCharacterClicked;
	bool m_buttonLevelClicked;

	void handlePlayButton();
	
public:
	MenuState(sf::RenderWindow* window,sf::Font &font);
	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font) override;
	bool isActive() override;
	GameState* nextState() override;
	void handleInputEvent(const sf::Event*& ev, const sf::Font& font) override;
	void drawState(sf::RenderWindow* window) override;
};

