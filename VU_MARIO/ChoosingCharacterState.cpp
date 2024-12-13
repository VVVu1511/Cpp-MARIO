#include "ChoosingCharacterState.h"

ChoosingCharacterState::ChoosingCharacterState(sf::RenderWindow* window, sf::Font& font){
	this->view = View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));

	this->m_contents = { "MARIO","LUIGI" };
	this->m_all_buttons = std::vector<sf::RectangleShape>(2);
	this->m_texts = std::vector<sf::Text>(2);
	this->m_Input = "";

	this->setAttributes<sf::RectangleShape>(this->m_all_buttons, {}, std::vector<sf::Color>(this->m_all_buttons.size(), BUTTON_COLOR), font, std::vector<sf::Vector2f>(this->m_all_buttons.size(), sf::Vector2f(1200.f, 100.f)), {}, {}, {}, { sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 110.f) });
	this->setAttributes<sf::Text>(this->m_texts, this->m_contents, std::vector<sf::Color>(this->m_texts.size(), sf::Color(252, 222, 202)), font, {}, {}, {}, { 50,50 }, { sf::Vector2f(5.f, 5.f), sf::Vector2f(5.f, 115.f) });
}

void ChoosingCharacterState::execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font){
	this->drawState(window);
	this->handleInputEvent(ev, font);
	view.setForWindow(window);
}

bool ChoosingCharacterState::isActive()
{
	return this->active;
}


GameState* ChoosingCharacterState::nextState()
{
	return nullptr;
}

void ChoosingCharacterState::drawState(sf::RenderWindow* window){
	this->draw<sf::RectangleShape>(window, this->m_all_buttons);
	this->draw<sf::Text>(window, this->m_texts);
}

void ChoosingCharacterState::handleInputEvent(const sf::Event*& ev, const sf::Font& font){
	if (ev->type == sf::Event::MouseButtonPressed && ev->mouseButton.button == sf::Mouse::Left) {
		sf::Vector2f mousePos(ev->mouseButton.x, ev->mouseButton.y);

		this->m_Input = this->findContentOfButtonClicked(mousePos, this->m_all_buttons, this->m_texts);

	}
}
