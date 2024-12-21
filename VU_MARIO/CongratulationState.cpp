#include "CongratulationState.h"
#include "MenuState.h"

CongratulationState::CongratulationState() {
	std::string content = "CONGRATULATION";
	text.setString(content);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color(255, 255, 255, 128));
	this->active = true;
	this->delay_time = 2;

	this->view = View(sf::FloatRect(0, 0, 1200, 576));

	this->text.setPosition(1200 / 2 - text.getGlobalBounds().width / 2, 576 / 2 - text.getGlobalBounds().height / 2);
}

CongratulationState::CongratulationState(sf::RenderWindow* window) : CongratulationState() {
	this->view = View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));

	this->text.setPosition(window->getSize().x / 2 - text.getGlobalBounds().width / 2, window->getSize().y / 2 - text.getGlobalBounds().height / 2);
}

void CongratulationState::execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font){
	if (this->delay_time < 0) {
		this->active = false;
		this->m_nextState = new MenuState(window,font);
	}

	this->delay_time -= deltaTime;

	text.setFont(font);
	
	this->drawState(window);

	view.setForWindow(window);
}

bool CongratulationState::isActive(){

	return this->active;
}



void CongratulationState::drawState(sf::RenderWindow* window){
	window->draw(text);
}

void CongratulationState::handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window){

}
