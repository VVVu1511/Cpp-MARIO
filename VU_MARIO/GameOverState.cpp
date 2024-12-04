#include "GameOverState.h"

GameOverState::GameOverState(){
	std::string content = "GAME OVER!";
	text.setString(content);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color(255, 255, 255, 128));
}

GameOverState::~GameOverState(){
	
}

void GameOverState::execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font){
	text.setFont(font);
	text.setPosition(window->getSize().x / 2 - text.getGlobalBounds().width / 2, window->getSize().y / 2 - text.getGlobalBounds().height / 2);

	window->draw(text);
}

bool GameOverState::isActive(){

	return false;
}
