#include "MenuState.h"
#include <iostream>

void MenuState::drawMenu(sf::RenderWindow* window){
    window->draw(this->m_menu_frames);
    this->draw<sf::RectangleShape>(window, this->m_menu_all_buttons);
    this->draw<sf::Text>(window, this->m_menu_texts);
}

void MenuState::drawChoosingLevel(sf::RenderWindow* window){
    this->draw<sf::RectangleShape>(window, this->m_level_all_buttons);
    this->draw<sf::Text>(window, this->m_level_texts);
}

void MenuState::drawChoosingCharacter(sf::RenderWindow* window){
    this->draw<sf::RectangleShape>(window, this->m_character_all_buttons);
    this->draw<sf::Text>(window, this->m_character_texts);
}

void MenuState::handleInputEvent(const sf::Event*& ev, const sf::Font& font){
    if (this->m_isChoosingLevel == true) {
        this->handleChoosingLevelButton(ev);
        return;
    }

    else if (this->m_isChoosingCharacter == true) {
        this->handleChoosingCharacterButton(ev);
        return;
    }

    if (ev->type == sf::Event::MouseButtonPressed && ev->mouseButton.button == sf::Mouse::Left) {

        sf::Vector2f mousePos(ev->mouseButton.x, ev->mouseButton.y);

        if (this->m_menu_all_buttons[0].getGlobalBounds().contains(mousePos)) {
            this->m_menu_all_buttons[0].setFillColor(CLICKED_COLOR);
            this->handlePlayButton();
        }

        else if (this->m_menu_all_buttons[1].getGlobalBounds().contains(mousePos)) {
            this->m_isChoosingLevel = true;
            this->m_delay_levelTime = 0.2;
            this->m_menu_all_buttons[1].setFillColor(CLICKED_COLOR);
        }

        else if (this->m_menu_all_buttons[2].getGlobalBounds().contains(mousePos)) {
            this->m_isChoosingCharacter = true;
            this->m_delay_characterTime = 0.2;
            this->m_menu_all_buttons[2].setFillColor(CLICKED_COLOR);
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

void MenuState::handlePlayButton(){
    if (this->m_levelInput != "" && this->m_characterInput != "") {
        this->active = false;
    }
}

void MenuState::handleChoosingLevelButton(const sf::Event*& ev){
    if (ev->type == sf::Event::MouseButtonPressed && ev->mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(ev->mouseButton.x, ev->mouseButton.y);
        
        this->m_levelInput = this->findContentOfButtonClicked(mousePos, this->m_level_all_buttons, this->m_level_texts);

        if (this->m_levelInput != "") {
            this->m_isChoosingLevel = false;
        }
    }
}

void MenuState::handleChoosingCharacterButton(const sf::Event*& ev){
    if (ev->type == sf::Event::MouseButtonPressed && ev->mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(ev->mouseButton.x, ev->mouseButton.y);

        this->m_characterInput = this->findContentOfButtonClicked(mousePos, this->m_character_all_buttons, this->m_character_texts);

        if (this->m_characterInput != "") {
            this->m_isChoosingCharacter = false;
        }
    }
}

std::string MenuState::findContentOfButtonClicked(const sf::Vector2f& mousePos, const std::vector<sf::RectangleShape>& all_buttons, const std::vector<sf::Text>& texts){
    int size = all_buttons.size();

    for (int i = 0; i < size; i++) {
        if (all_buttons[i].getGlobalBounds().contains(mousePos)) {
            return texts[i].getString();
        }
    }

    return "";
}

MenuState::MenuState(sf::RenderWindow* window, sf::Font& font){
    this->active = true;
    this->m_levelInput = "";
    this->m_delay_levelTime = 0;
    this->m_characterInput = "";
    this->m_delay_characterTime = 0;
    this->m_isChoosingLevel = this->m_isChoosingCharacter = false;

    this->view = View(sf::FloatRect(0, 0,window->getSize().x, window->getSize().y));

    this->m_menu_contents = {"SUPER","MARIO BROS","PLAY","CHOOSE LEVEL","CHOOSE CHARACTER"};
    this->m_menu_texts = std::vector<sf::Text>(5);
    this->m_menu_all_buttons = std::vector<sf::RectangleShape>(3);

    this->m_level_contents = { "WORLD 1 - EASY","WORLD 2 - MEDIUM","WORLD 3 - HARD" };
    this->m_level_all_buttons = std::vector<sf::RectangleShape>(3);
    this->m_level_texts = std::vector<sf::Text>(3);

    this->m_character_contents = { "MARIO","LUIGI" };
    this->m_character_all_buttons = std::vector<sf::RectangleShape>(2);
    this->m_character_texts = std::vector<sf::Text>(2);


    this->setAttributes<sf::RectangleShape>(this->m_menu_all_buttons, {}, std::vector<sf::Color>(this->m_menu_all_buttons.size(), BUTTON_COLOR), font, std::vector<sf::Vector2f>(this->m_menu_all_buttons.size(), sf::Vector2f(600.f, 50.f)), {}, {}, {}, { sf::Vector2f(300.f, 360.f), sf::Vector2f(300.f, 420.f), sf::Vector2f(300.f, 480.f) });
    this->setAttributes<sf::Text>(this->m_menu_texts, this->m_menu_contents, std::vector<sf::Color>(this->m_menu_texts.size(), sf::Color(252, 222, 202)), font, {}, {}, {}, {60,75,30,30,30}, {sf::Vector2f(350.f, 100.f), sf::Vector2f(350.f, 170.f) ,sf::Vector2f(550.f, 370.f), sf::Vector2f(470.f, 430.f), sf::Vector2f(450.f, 490.f)});
    this->m_menu_frames.setSize(sf::Vector2f(600.f, 300.f));
    this->m_menu_frames.setPosition(sf::Vector2f(300.f, 50.f));
    this->m_menu_frames.setFillColor(BUTTON_COLOR);

    this->setAttributes<sf::RectangleShape>(this->m_level_all_buttons, {}, std::vector<sf::Color>(this->m_level_all_buttons.size(), BUTTON_COLOR), font, std::vector<sf::Vector2f>(this->m_level_all_buttons.size(), sf::Vector2f(1200.f, 100.f)), {}, {}, {}, { sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 110.f), sf::Vector2f(0.f, 220.f) });
    this->setAttributes<sf::Text>(this->m_level_texts, this->m_level_contents, std::vector<sf::Color>(this->m_level_texts.size(), sf::Color(252, 222, 202)), font,{}, {}, {}, std::vector<int>(this->m_level_texts.size(), 50), {sf::Vector2f(5.f, 5.f), sf::Vector2f(5.f, 115.f) ,sf::Vector2f(5.f, 225.f)});

    this->setAttributes<sf::RectangleShape>(this->m_character_all_buttons, {}, std::vector<sf::Color>(this->m_character_all_buttons.size(), BUTTON_COLOR), font, std::vector<sf::Vector2f>(this->m_character_all_buttons.size(), sf::Vector2f(1200.f, 100.f)), {}, {}, {}, { sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 110.f) });
    this->setAttributes<sf::Text>(this->m_character_texts, this->m_character_contents, std::vector<sf::Color>(this->m_character_texts.size(), sf::Color(252, 222, 202)), font, {}, {}, {}, {50,50}, {sf::Vector2f(5.f, 5.f), sf::Vector2f(5.f, 115.f)});
}

void MenuState::execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font){
    this->handleInputEvent(ev,font);

    if (this->m_isChoosingLevel == true) {
        if (this->m_delay_levelTime <= 0) {
            this->drawChoosingLevel(window);
        }
        else {
            this->m_delay_levelTime -= deltaTime;
            this->drawMenu(window);
        }
    }

    else if (this->m_isChoosingCharacter == true) {
        if (this->m_delay_characterTime <= 0) {
            this->drawChoosingCharacter(window);
        }
        else {
            this->m_delay_characterTime -= deltaTime;
            this->drawMenu(window);
        }
    }

    else {
        this->drawMenu(window);
    }

    view.setForWindow(window);	
}

bool MenuState::isActive(){
    return this->active;
}
