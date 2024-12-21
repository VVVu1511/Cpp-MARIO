#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <vector>

enum class InputType {
	level = 1,
	character = 2,
};

class MenuState : public GameState{

private:
	static PlayableCharacterType m_characterInput;
	static int m_levelInput;

	sf::RectangleShape m_menu_frames;
	std::vector<sf::RectangleShape> m_menu_all_buttons;
	std::vector<std::string> m_menu_contents;
	std::vector<sf::Text>m_menu_texts;

	bool m_buttonCharacterClicked;
	bool m_buttonLevelClicked;

	void handlePlayButton();
	
public:
	MenuState(sf::RenderWindow* window,const sf::Font &font);
	MenuState(sf::RenderWindow* window, const sf::Font& font,const int &mapNum);
	MenuState(sf::RenderWindow* window, const sf::Font& font, PlayableCharacterType type);

	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font) override;
	bool isActive() override;
	void handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window) override;
	void drawState(sf::RenderWindow* window) override;
};

