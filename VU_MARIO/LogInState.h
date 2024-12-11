#pragma once
#include "GameState.h"

class LogInState : public GameState{
private:

	template<typename T>
	void setAttributes(std::vector<T>& vectors, const std::vector<std::string>& contents, const std::vector<sf::Color>& color, const sf::Font& font, const std::vector<sf::Vector2f>& size, const std::vector<sf::Color>& outlineColor, const std::vector<int>& outlineThicknessSize, const std::vector<int>& characterSize, const std::vector<sf::Vector2f>& position);

    template<typename T>
    void draw(sf::RenderWindow* window, std::vector<T>& vectors);

	bool m_inputBoxActive = false;
	float m_current_time;
	float m_allow_input_time;
	unsigned int max_chars;

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
	void handleEventForInput(const sf::Event* ev, const float& deltaTime, sf::RenderWindow* window);
	void drawAll(sf::RenderWindow* window);
	void handleLogInButton(const sf::Event* ev);
	void handleExitButton(sf::RenderWindow* window,const sf::Event* ev);
	bool checkValidInput();

public:
	LogInState();
	LogInState(sf::RenderWindow* window, const sf::Font& font);
	void execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font) override;
	bool isActive() override;
};

template<typename T>
void LogInState::setAttributes(std::vector<T>& vectors, const std::vector<std::string>& contents, const std::vector<sf::Color>& color, const sf::Font& font, const std::vector<sf::Vector2f>& size, const std::vector<sf::Color>& outlineColor, const std::vector<int>& outlineThicknessSize, const std::vector<int>& characterSize,const std::vector<sf::Vector2f>&position) {
	std::vector<bool>canSet(7,true);

	if (contents.size() == 0) {
		canSet[0] = false;
		canSet[2] = false;
	}

	if (color.size() == 0) canSet[1] = false;

	if (size.size() == 0) canSet[3] = false;

	if (outlineColor.size() == 0) canSet[4] = false;

	if (outlineThicknessSize.size() == 0) canSet[5] = false;

	if (characterSize.size() == 0) canSet[6] = false;


	for (size_t i = 0; i < vectors.size(); ++i) {
		if constexpr (std::is_same_v<T, sf::Text>) {
			if (canSet[0]) vectors[i].setString(contents[i]);
			if (canSet[1]) vectors[i].setFillColor(color[i]);
			if (canSet[2]) vectors[i].setFont(font);
			if (canSet[6]) vectors[i].setCharacterSize(characterSize[i]);
		}
		else if constexpr (std::is_same_v<T, sf::RectangleShape>) {
			if (canSet[1]) vectors[i].setFillColor(color[i]);
			if (canSet[3]) vectors[i].setSize(size[i]);
			if (canSet[4]) vectors[i].setOutlineColor(outlineColor[i]);
			if (canSet[5]) vectors[i].setOutlineThickness(outlineThicknessSize[i]);
		}
		vectors[i].setPosition(position[i]);
	}
}

template<typename T>
void LogInState::draw(sf::RenderWindow* window, std::vector<T>& vectors) {
    for (int i = 0; i < vectors.size(); i++) {
        window->draw(vectors[i]);
    }
}


