#include "GameState.h"
#include <iostream>

std::string GameState::findContentOfButtonClicked(const sf::Vector2f& mousePos, const std::vector<sf::RectangleShape>& all_buttons, const std::vector<sf::Text>& texts) {
    int size = all_buttons.size();

    for (int i = 0; i < size; i++) {
        if (all_buttons[i].getGlobalBounds().contains(mousePos)) {
            return texts[i].getString();
        }
    }

    return "";
}

GameState::GameState(){
	this->active = true;
    this->m_nextState = nullptr;
}

GameState::~GameState(){
    //delete this->m_nextState;
}

GameState* GameState::nextState()
{
    std::cout << "returning next state: " << this->m_nextState << "\n";
    return this->m_nextState;
}








