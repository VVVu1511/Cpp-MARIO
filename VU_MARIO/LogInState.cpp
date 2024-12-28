#include "LogInState.h"
#include "View.h"
#include<iostream>
#include "MenuState.h"

#include <iostream>

LogInState::LogInState(){}

LogInState::LogInState(sf::RenderWindow* window, const sf::Font& font) {
    this->valid_username = { "" };
    this->m_delay_log_in = 0;
    this->m_logInClicked = 0;
    this->valid_password = { "" };
    this->active = true;
    this->view = View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
    this->max_chars = 40;
    this->m_current_time = 0;
    this->m_inputBoxActive = 0;
    this->m_allow_input_time = 0.07;

    this->content = { "MARIO 1985","Username:","Password:","LOG IN","EXIT" };
    this->all_not_input_texts = std::vector<sf::Text>(5);
    this->inputText = std::vector<std::string>(2);
    this->inputDisplay = std::vector<sf::Text>(2);
    this->inputBoxes = std::vector<sf::RectangleShape>(2);
    this->frames = std::vector<sf::RectangleShape>(2);
    this->all_buttons = std::vector<sf::RectangleShape>(2);

    this->all_not_input_texts_position = { sf::Vector2f(400.f, 50.f) ,sf::Vector2f(230.f, 220.f) ,sf::Vector2f(230.f, 350.f) ,sf::Vector2f(360.f, 520.f),sf::Vector2f(760.f, 520.f) };
    this->inputDisplay_position = { sf::Vector2f(505.f, 230.f) ,sf::Vector2f(505.f, 360.f) };
    this->inputBoxes_position = { sf::Vector2f(500.f, 225.f) ,sf::Vector2f(500.f, 355.f) };
    this->frames_position = { sf::Vector2f(200.f, 150.f), sf::Vector2f(200.f, 460.f) };
    this->all_buttons_position = { sf::Vector2f(350.f, 510.f) ,sf::Vector2f(738.f, 510.f) };

    this->setAttributes<sf::RectangleShape>(this->inputBoxes, {}, std::vector<sf::Color>(this->inputBoxes.size(), sf::Color::White), font, std::vector<sf::Vector2f>(this->inputBoxes.size(), sf::Vector2f(400.f, 30.f)), {}, { std::vector<int>(this->inputBoxes.size(),2) }, {}, this->inputBoxes_position);
    this->setAttributes<sf::Text>(this->inputDisplay, this->inputText, std::vector<sf::Color>(this->inputDisplay.size(), sf::Color::Black), font, std::vector<sf::Vector2f>(this->inputDisplay.size(), sf::Vector2f(400.f, 30.f)), {}, { std::vector<int>(this->inputDisplay.size(),2) }, { std::vector<int>(this->inputDisplay.size(),20) }, this->inputDisplay_position);
    this->setAttributes<sf::Text>(this->all_not_input_texts, this->content, std::vector<sf::Color>(this->all_not_input_texts.size(), sf::Color::Red), font, std::vector<sf::Vector2f>(this->all_not_input_texts.size(), sf::Vector2f(400.f, 50.f)), {}, { std::vector<int>(this->all_not_input_texts.size(),2) }, { 60,30,30,20,20 }, this->all_not_input_texts_position);
    this->setAttributes<sf::RectangleShape>(this->frames, {}, std::vector<sf::Color>(this->frames.size(), sf::Color::White), font, { sf::Vector2f(800.f, 300.f),sf::Vector2f(800.f, 100.f) }, {}, { std::vector<int>(this->frames.size(),2) }, {}, this->frames_position);
    this->setAttributes<sf::RectangleShape>(this->all_buttons, {}, std::vector<sf::Color>(this->all_buttons.size(), sf::Color::Green), font, std::vector<sf::Vector2f>(this->all_buttons.size(), sf::Vector2f(100.f, 50.f)), {}, { std::vector<int>(this->all_buttons.size(),2) }, {}, this->all_buttons_position);

    for (int i = 0; i < inputDisplay.size(); i++) {
        this->inputText[i] = "";
    }
}

void LogInState::execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev, const sf::Font& font){  
    this->handleEventForInput(ev, deltaTime,window,font);
    this->drawState(window);
    this->view.setForWindow(window);
}

bool LogInState::isActive(){
	return this->active;
}

void LogInState::handleTextInput(std::string &input, const sf::Event* ev) {
    if (std::isprint(ev->text.unicode) && input.size() < max_chars) {
        input += static_cast<char>(ev->text.unicode);
    }
    else if (ev->text.unicode == '\b' && !input.empty()) {
        input.pop_back();
    }
}

void LogInState::handleEventForInput(const sf::Event* ev, const float& deltaTime, sf::RenderWindow* window, const sf::Font& font){
    bool canInput = false;

    this->m_current_time += deltaTime;

    if (this->m_current_time >= this->m_allow_input_time) {
        this->m_allow_input_time += 0.07;
        canInput = true;
    }

    if (ev->type == sf::Event::MouseButtonPressed && ev->mouseButton.button == sf::Mouse::Left) {

        sf::Vector2f mousePos(ev->mouseButton.x, ev->mouseButton.y);

        if (this->inputBoxes[0].getGlobalBounds().contains(mousePos)) {
            m_inputBoxActive = 1;
            this->inputBoxes[0].setOutlineColor(sf::Color::Green);
            this->inputBoxes[1].setOutlineColor(sf::Color::Black);
        }

        else if (this->inputBoxes[1].getGlobalBounds().contains(mousePos)) {
            m_inputBoxActive = 1;
            this->inputBoxes[0].setOutlineColor(sf::Color::Black);
            this->inputBoxes[1].setOutlineColor(sf::Color::Green);
        }

        else if (m_inputBoxActive == 1) {
            m_inputBoxActive = 0;
            this->inputBoxes[0].setOutlineColor(sf::Color::Black);
            this->inputBoxes[1].setOutlineColor(sf::Color::Black);
        }
    }

    if (canInput && m_inputBoxActive == 1 && ev->type == sf::Event::TextEntered) {

        if (this->inputBoxes[0].getOutlineColor() == sf::Color::Green) {
            handleTextInput(this->inputText[0], ev);
        }

        else if (this->inputBoxes[1].getOutlineColor() == sf::Color::Green) {
            handleTextInput(this->inputText[1], ev);
        }
    }

    this->inputDisplay[0].setString(this->inputText[0]);
    this->inputDisplay[1].setString(std::string(this->inputText[1].size(), '*'));
    this->handleLogInButton(ev,deltaTime,window,font);
    this->handleExitButton(window, ev,deltaTime);
}

void LogInState::drawState(sf::RenderWindow* window){
    draw<sf::RectangleShape>(window, this->inputBoxes);
    draw<sf::Text>(window, this->inputDisplay);
    draw<sf::RectangleShape>(window, this->all_buttons);
    draw<sf::Text>(window, this->all_not_input_texts);
}

void LogInState::handleInputEvent(const sf::Event*& ev, const sf::Font& font, sf::RenderWindow* window){

}

void LogInState::handleLogInButton(const sf::Event* ev, const float& deltaTime, sf::RenderWindow* window, const sf::Font& font){
    
    if (ev->type == sf::Event::MouseButtonPressed && ev->mouseButton.button == sf::Mouse::Left) {

        sf::Vector2f mousePos(ev->mouseButton.x, ev->mouseButton.y);

        if (this->all_buttons[0].getGlobalBounds().contains(mousePos)) {
            this->all_buttons[0].setFillColor(CLICKED_COLOR);
            this->m_logInClicked = 1;
            this->m_delay_log_in = 0.2;
        }
    }

    if (this->m_logInClicked == 1) {
        if (this->m_delay_log_in > 0) {
            this->m_delay_log_in -= deltaTime;
            return;
        }

        if (this->checkValidInput() == true) {
            this->active = false;
            std::cout << "login success??\n";
            this->m_nextState = new MenuState(window, font);
            std::cout << "login success??, menustate = " << this->m_nextState << "\n";
            sf::sleep(sf::seconds(0.2));
        }

        else {
            this->m_logInClicked = 0;
        }
    }
}

void LogInState::handleExitButton(sf::RenderWindow* window,const sf::Event* ev, const float& deltaTime){
    if (ev->type == sf::Event::MouseButtonPressed && ev->mouseButton.button == sf::Mouse::Left) {

        sf::Vector2f mousePos(ev->mouseButton.x, ev->mouseButton.y);

        if (this->all_buttons[1].getGlobalBounds().contains(mousePos)) {
            this->all_buttons[1].setFillColor(CLICKED_COLOR);
            sf::sleep(sf::seconds(0.2));
            window->close();
        }
    }
}

bool LogInState::checkValidInput() {
    std::bitset<1>contain_username = 0;
    std::bitset<1>contain_password = 0;

    for (std::string username : valid_username) {
        if (inputText[0] == username) {
            contain_username = 1;
            break;
        }
    }

    for (std::string password : valid_password) {
        if (inputText[1] == password) {
            contain_password = 1;
            break;
        }
    }

    if ((contain_username != 1) || (contain_password != 1)) return false;

    return true;
}









