#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <vector>

class MenuState : public GameState{

private:	
	sf::RectangleShape m_menu_frames;
	std::vector<sf::RectangleShape> m_menu_all_buttons;
	std::vector<sf::RectangleShape> m_level_all_buttons;
	std::vector<sf::RectangleShape> m_character_all_buttons;
	std::vector<std::string> m_menu_contents;
	std::vector<std::string> m_level_contents;
	std::vector<std::string> m_character_contents;
	std::vector<sf::Text>m_menu_texts;
	std::vector<sf::Text>m_level_texts;
	std::vector<sf::Text>m_character_texts;

	float m_delay_levelTime;
	float m_delay_characterTime;

	std::string m_levelInput;
	std::string m_characterInput;

	bool m_isChoosingLevel;
	bool m_isChoosingCharacter;

	void drawMenu(sf::RenderWindow* window);
	void drawChoosingLevel(sf::RenderWindow* window);
	void drawChoosingCharacter(sf::RenderWindow* window);
	void handleInputEvent(const sf::Event* &ev, const sf::Font& font);
	void handlePlayButton();
	
	void handleChoosingLevelButton(const sf::Event*& ev);
	void handleChoosingCharacterButton(const sf::Event*& ev);
	std::string findContentOfButtonClicked(const sf::Vector2f& mousePos,const std::vector<sf::RectangleShape>& all_buttons,const std::vector<sf::Text>&texts);

public:
	MenuState(sf::RenderWindow* window,sf::Font &font);
	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font) override;
	bool isActive() override;
};

