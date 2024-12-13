#pragma once
#include<SFML/Graphics.hpp>
#include "View.h"
#include <bitset>


#define CLICKED_COLOR sf::Color(255,255,255,128)
#define BUTTON_COLOR sf::Color(211, 78, 76)



enum class StateOfGame {
	menu = 1,
	playing = 2,
	changingMap = 3,
	gameover = 4,
	login = 5,
};

class Observer;

class GameState{

protected:
	bool active = false;
	View view;
	bool isCreated = false;
	float delay_time;

	template<typename T>
	void setAttributes(std::vector<T>& vectors, const std::vector<std::string>& contents, const std::vector<sf::Color>& color, const sf::Font& font, const std::vector<sf::Vector2f>& size, const std::vector<sf::Color>& outlineColor, const std::vector<int>& outlineThicknessSize, const std::vector<int>& characterSize, const std::vector<sf::Vector2f>& position);

	template<typename T>
	void draw(sf::RenderWindow* window, std::vector<T>& vectors);

	virtual std::string findContentOfButtonClicked(const sf::Vector2f& mousePos, const std::vector<sf::RectangleShape>& all_buttons, const std::vector<sf::Text>& texts);

public:
	GameState();
	virtual ~GameState() = default;
	virtual void execute(sf::RenderWindow* window,std::vector<Observer*>&observers,GameState* gameState, const float& deltaTime, const sf::Event* ev,const sf::Font& font) = 0;
	virtual bool isActive() = 0;
	virtual GameState* nextState() = 0;
	virtual void drawState(sf::RenderWindow* window) = 0;
	virtual void handleInputEvent(const sf::Event*& ev, const sf::Font& font) = 0;

};

template<typename T>
void GameState::setAttributes(std::vector<T>& vectors, const std::vector<std::string>& contents, const std::vector<sf::Color>& color, const sf::Font& font, const std::vector<sf::Vector2f>& size, const std::vector<sf::Color>& outlineColor, const std::vector<int>& outlineThicknessSize, const std::vector<int>& characterSize, const std::vector<sf::Vector2f>& position) {
	std::vector<bool>canSet(8, true);

	if (contents.size() == 0) {
		canSet[0] = false;
		canSet[2] = false;
	}

	if (color.size() == 0) canSet[1] = false;

	if (size.size() == 0) canSet[3] = false;

	if (outlineColor.size() == 0) canSet[4] = false;

	if (outlineThicknessSize.size() == 0) canSet[5] = false;

	if (characterSize.size() == 0) canSet[6] = false;

	if (position.size() == 0) canSet[7] = false;


	for (size_t i = 0; i < vectors.size(); ++i) {
		if constexpr (std::is_same_v<T, sf::Text>) {
			if (canSet[0] == true) vectors[i].setString(contents[i]);
			if (canSet[1] == true) vectors[i].setFillColor(color[i]);
			if (canSet[2] == true) vectors[i].setFont(font);
			if (canSet[6] == true) vectors[i].setCharacterSize(characterSize[i]);
		}
		else if constexpr (std::is_same_v<T, sf::RectangleShape>) {
			if (canSet[1] == true) vectors[i].setFillColor(color[i]);
			if (canSet[3] == true) vectors[i].setSize(size[i]);
			if (canSet[4] == true) vectors[i].setOutlineColor(outlineColor[i]);
			if (canSet[5] == true) vectors[i].setOutlineThickness(outlineThicknessSize[i]);
		}
		if(canSet[7] == true) vectors[i].setPosition(position[i]);
	}
}


template<typename T>
void GameState::draw(sf::RenderWindow* window, std::vector<T>& vectors) {
	for (int i = 0; i < vectors.size(); i++) {
		window->draw(vectors[i]);
	}
}
