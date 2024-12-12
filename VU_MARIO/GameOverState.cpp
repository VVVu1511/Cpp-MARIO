#include "GameOverState.h"

GameOverState::GameOverState(){
	std::string content = "GAME OVER!";
	text.setString(content);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color(255, 255, 255, 128));
	this->active = true;
}

GameOverState::~GameOverState(){
	
}

void GameOverState::execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font){
	
	if (expiredTime < 0) this->active = false;

	expiredTime -= deltaTime;
	
	if (!isCreated) {
		view = View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
		isCreated = true;
	}
	
	
	
	text.setFont(font);
	text.setPosition(window->getSize().x / 2 - text.getGlobalBounds().width / 2, window->getSize().y / 2 - text.getGlobalBounds().height / 2);

	window->draw(text);

	view.setForWindow(window);
}

bool GameOverState::isActive(){

	return this->active;
}

StateOfGame GameOverState::nextState(){
	return StateOfGame::menu;
}
