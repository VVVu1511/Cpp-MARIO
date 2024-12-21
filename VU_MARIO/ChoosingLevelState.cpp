#include "ChoosingLevelState.h"
#include "MenuState.h"

ChoosingLevelState::ChoosingLevelState(sf::RenderWindow* window, const sf::Font& font){
    this->view = View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));

    this->m_contents = { "WORLD 1 - EASY","WORLD 2 - MEDIUM","WORLD 3 - HARD" };
    this->m_all_buttons = std::vector<sf::RectangleShape>(3);
    this->m_texts = std::vector<sf::Text>(3);

    this->setAttributes<sf::RectangleShape>(this->m_all_buttons, {}, std::vector<sf::Color>(this->m_all_buttons.size(), BUTTON_COLOR), font, std::vector<sf::Vector2f>(this->m_all_buttons.size(), sf::Vector2f(1200.f, 100.f)), {}, {}, {}, { sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 110.f), sf::Vector2f(0.f, 220.f) });
    this->setAttributes<sf::Text>(this->m_texts, this->m_contents, std::vector<sf::Color>(this->m_texts.size(), sf::Color(252, 222, 202)), font, {}, {}, {}, std::vector<int>(this->m_texts.size(), 50), { sf::Vector2f(5.f, 5.f), sf::Vector2f(5.f, 115.f) ,sf::Vector2f(5.f, 225.f) });
}

void ChoosingLevelState::drawState(sf::RenderWindow* window){
    this->draw<sf::RectangleShape>(window, this->m_all_buttons);
    this->draw<sf::Text>(window, this->m_texts);
}

void ChoosingLevelState::execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font){
    this->drawState(window);
    this->handleInputEvent(ev, font,window);
    view.setForWindow(window);
}

bool ChoosingLevelState::isActive(){
    return this->active;
}

GameState* ChoosingLevelState::nextState(){

    return nullptr;
}

void ChoosingLevelState::handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window){
    if (ev->type == sf::Event::MouseButtonPressed && ev->mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(ev->mouseButton.x, ev->mouseButton.y);

        this->m_Input = findContentOfButtonClicked(mousePos, this->m_all_buttons, this->m_texts);

        int mapNum = -1;

        for (int i = 0; i < 3; i++) {
            if (this->m_Input == m_contents[i]) {
                mapNum = i + 1;
                break;
            }
        }

        if (mapNum != -1) {
            this->m_nextState = new MenuState(window,font,mapNum);
            this->active = false;
            sf::sleep(sf::seconds(0.2));
        }
    }
}
