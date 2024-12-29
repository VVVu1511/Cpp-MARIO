#include "GameOverState.h"
#include "MenuState.h"

GameOverState::GameOverState(){
	std::string content = "GAME OVER!";
	text.setString(content);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color(255, 255, 255, 128));
	this->active = true;
	this->delay_time = 2;
}

GameOverState::GameOverState(sf::RenderWindow* window) : GameOverState(){
	this->view = View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
}

GameOverState::~GameOverState(){
	
}

void GameOverState::execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font){
	
	if (this->delay_time < 0) {
		this->active = false;
		this->m_nextState = new MenuState(window, font);
	}

	this->delay_time -= deltaTime;
	
	text.setFont(font);
	text.setPosition(window->getSize().x / 2 - text.getGlobalBounds().width / 2, window->getSize().y / 2 - text.getGlobalBounds().height / 2);

	window->draw(text);

	view.setForWindow(window);
}

bool GameOverState::isActive(){

	return this->active;
}

GameState* GameOverState::nextState() {
	return m_nextState;
}

void GameOverState::handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window){}

void GameOverState::drawState(sf::RenderWindow* window){

}
