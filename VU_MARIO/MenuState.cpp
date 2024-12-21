#include "MenuState.h"
#include <iostream>
#include "AssetManager.h"
#include "PlayingState.h"
#include "ChoosingCharacterState.h"
#include "ChoosingLevelState.h"

int MenuState::m_levelInput = -1;
PlayableCharacterType MenuState::m_characterInput = PlayableCharacterType::none;

void MenuState::drawState(sf::RenderWindow* window){
    window->draw(this->m_menu_frames);
    this->draw<sf::RectangleShape>(window, this->m_menu_all_buttons);
    this->draw<sf::Text>(window, this->m_menu_texts);
}

void MenuState::handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window){
    if (ev->type == sf::Event::MouseButtonPressed && ev->mouseButton.button == sf::Mouse::Left) {

        sf::Vector2f mousePos(ev->mouseButton.x, ev->mouseButton.y);

        if (this->m_menu_all_buttons[0].getGlobalBounds().contains(mousePos)) {
            this->m_menu_all_buttons[0].setFillColor(CLICKED_COLOR);
            this->handlePlayButton();
        }

        else if (this->m_menu_all_buttons[1].getGlobalBounds().contains(mousePos)) {
            this->m_menu_all_buttons[1].setFillColor(CLICKED_COLOR);
            this->active = false;
            this->m_nextState = new ChoosingLevelState(window,font);
            sf::sleep(sf::seconds(0.2));
        }

        else if (this->m_menu_all_buttons[2].getGlobalBounds().contains(mousePos)) {
            this->m_menu_all_buttons[2].setFillColor(CLICKED_COLOR);
            this->active = false;
            this->m_nextState = new ChoosingCharacterState(window, font);
            sf::sleep(sf::seconds(0.2));
        }
    }

    else {
        for (sf::RectangleShape &button : this->m_menu_all_buttons) {
            button.setFillColor(BUTTON_COLOR);
        }
    }

    /*if (ev->type == sf::Event::MouseButtonPressed) {

        sf::Vector2i position = sf::Mouse::getPosition(*window);

        sf::Vector2f float_position((float)position.x, (float)position.y);

        if (button.getGlobalBounds().contains(float_position)) {
            button.setFillColor(sf::Color(255, 255, 255, 128));
            this->active = false;
        }

        else if (button2.getGlobalBounds().contains(float_position)) {
            button2.setFillColor(sf::Color(255, 255, 255, 128));
        }

        else if (button3.getGlobalBounds().contains(float_position)) {
            button3.setFillColor(sf::Color(255, 255, 255, 128));
        }
    }

    if (ev->type == sf::Event::MouseButtonReleased) {
        button.setFillColor(BUTTON_COLOR);
        button2.setFillColor(BUTTON_COLOR);
        button3.setFillColor(BUTTON_COLOR);
    }

    if (ev->type == sf::Event::MouseWheelScrolled) {

    }*/

}

void MenuState::handlePlayButton() {
    if (m_characterInput != PlayableCharacterType::none && m_levelInput != -1) {
        this->active = false;
        std::pair<int, PlayableCharacterType> mapNum_and_character;
        mapNum_and_character.first = this->m_levelInput;
        mapNum_and_character.second = this->m_characterInput;
        this->m_nextState = new PlayingState(mapNum_and_character);
        sf::sleep(sf::seconds(0.2));
    }
}

MenuState::MenuState(sf::RenderWindow* window, const sf::Font& font){
    this->active = true;
    this->m_buttonCharacterClicked = false;
    this->m_buttonLevelClicked = false;
    
    this->view = View(sf::FloatRect(0, 0,window->getSize().x, window->getSize().y));

    this->m_menu_contents = {"SUPER","MARIO BROS","PLAY","CHOOSE LEVEL","CHOOSE CHARACTER"};
    this->m_menu_texts = std::vector<sf::Text>(5);
    this->m_menu_all_buttons = std::vector<sf::RectangleShape>(3);

    this->setAttributes<sf::RectangleShape>(this->m_menu_all_buttons, {}, std::vector<sf::Color>(this->m_menu_all_buttons.size(), BUTTON_COLOR), font, std::vector<sf::Vector2f>(this->m_menu_all_buttons.size(), sf::Vector2f(600.f, 50.f)), {}, {}, {}, { sf::Vector2f(300.f, 360.f), sf::Vector2f(300.f, 420.f), sf::Vector2f(300.f, 480.f) });
    this->setAttributes<sf::Text>(this->m_menu_texts, this->m_menu_contents, std::vector<sf::Color>(this->m_menu_texts.size(), sf::Color(252, 222, 202)), font, {}, {}, {}, {60,75,30,30,30}, {sf::Vector2f(350.f, 100.f), sf::Vector2f(350.f, 170.f) ,sf::Vector2f(550.f, 370.f), sf::Vector2f(470.f, 430.f), sf::Vector2f(450.f, 490.f)});
    this->m_menu_frames.setSize(sf::Vector2f(600.f, 300.f));
    this->m_menu_frames.setPosition(sf::Vector2f(300.f, 50.f));
    this->m_menu_frames.setFillColor(BUTTON_COLOR);

}

MenuState::MenuState(sf::RenderWindow* window, const sf::Font& font, const int& mapNum) : MenuState(window,font){
    this->m_levelInput = mapNum;
}

MenuState::MenuState(sf::RenderWindow* window, const sf::Font& font, PlayableCharacterType type) : MenuState(window,font){
    this->m_characterInput = type;
}

void MenuState::execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font){

    this->handleInputEvent(ev,font,window);
    
    this->drawState(window);
    
    view.setForWindow(window);	
}

bool MenuState::isActive(){
    return this->active;
}




