#pragma once
#include "GameState.h"

class LogInState : public GameState{
private:

	std::bitset<1> m_inputBoxActive;
	float m_current_time;
	float m_allow_input_time;
	unsigned int max_chars;
	float m_delay_log_in;
	std::bitset<1>m_logInClicked;

	std::vector<std::string>content;
	std::vector<sf::Text>all_not_input_texts;
	std::vector<sf::RectangleShape>all_buttons;
	std::vector<sf::RectangleShape>inputBoxes;
	std::vector<std::string>inputText;
	std::vector<sf::Text>inputDisplay;
	std::vector<sf::RectangleShape>frames;

	std::vector<sf::Vector2f>all_not_input_texts_position;
	std::vector<sf::Vector2f>all_buttons_position;
	std::vector<sf::Vector2f>inputBoxes_position;
	std::vector<sf::Vector2f>inputDisplay_position;
	std::vector<sf::Vector2f>frames_position;

	std::vector<std::string>valid_username;
	std::vector<std::string>valid_password;


	void handleTextInput(std::string& input,const sf::Event* ev);
	void handleEventForInput(const sf::Event* ev, const float& deltaTime, sf::RenderWindow* window, const sf::Font& font);
	void handleLogInButton(const sf::Event* ev, const float& deltaTime, sf::RenderWindow* window, const sf::Font& font);
	void handleExitButton(sf::RenderWindow* window,const sf::Event* ev, const float& deltaTime);
	bool checkValidInput();

public:
	LogInState();
	LogInState(sf::RenderWindow* window, const sf::Font& font);
	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font) override;
	bool isActive() override;
	void drawState(sf::RenderWindow* window) override;
	void handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window) override;
};






