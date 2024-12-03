#include "MenuState.h"
#include <iostream>

void MenuState::execute(sf::RenderWindow* window, std::vector<Observer*>& observers, GameState* gameState, const float& deltaTime, const sf::Event* ev){
    
    std::string content = "SUPER";
    std::string content2 = "MARIO BROS";
    std::string content3 = "PLAY";
    std::string content4 = "CHOOSE LEVEL";
    std::string content5 = "CHOOSE CHARACTER";

    sf::Text text, text2;
    sf::RectangleShape shape(sf::Vector2f(600.f, 300.f));
    sf::Font font;

    sf::RectangleShape button(sf::Vector2f(600.f, 50.f));
    button.setPosition(300.f, 360.f);
    button.setFillColor(sf::Color(211, 78, 76));

    sf::Text button1_text;

    button1_text.setPosition(sf::Vector2f(550.f, 370.f));

    button1_text.setString(content3);

    button1_text.setCharacterSize(30);

    button1_text.setFont(font);

    button1_text.setFillColor(sf::Color(252, 222, 202));

    sf::RectangleShape button2(sf::Vector2f(600.f, 50.f));
    button2.setPosition(300.f, 420.f);
    button2.setFillColor(sf::Color(211, 78, 76));
    sf::Text button2_text;

    button2_text.setPosition(sf::Vector2f(470.f, 430.f));

    button2_text.setString(content4);

    button2_text.setCharacterSize(30);

    button2_text.setFont(font);

    button2_text.setFillColor(sf::Color(252, 222, 202));

    sf::RectangleShape button3(sf::Vector2f(600.f, 50.f));
    button3.setPosition(300.f, 480.f);
    button3.setFillColor(sf::Color(211, 78, 76));

    sf::Text button3_text;

    button3_text.setPosition(sf::Vector2f(450.f, 490.f));

    button3_text.setString(content5);

    button3_text.setCharacterSize(30);

    button3_text.setFont(font);

    button3_text.setFillColor(sf::Color(252, 222, 202));

    if (!font.loadFromFile("../fonts/SuperMario256.ttf")) {
        std::cout << "Can not read file!";
    }

    shape.setPosition(sf::Vector2f(300.f, 50.f));

    shape.setFillColor(sf::Color(211, 78, 76));

    text.setPosition(sf::Vector2f(350.f, 100.f));

    text.setString(content);

    text.setCharacterSize(60);

    text.setFont(font);

    text2.setPosition(sf::Vector2f(350.f, 170.f));

    text2.setString(content2);

    text2.setCharacterSize(75);

    text2.setFont(font);

    text.setFillColor(sf::Color(252, 222, 202));

    text2.setFillColor(sf::Color(252, 222, 202));
   
    if (ev->type == sf::Event::MouseButtonPressed) {
        sf::Vector2i position = sf::Mouse::getPosition(*window);

        sf::Vector2f float_position((float)position.x, (float)position.y);

        if (button.getGlobalBounds().contains(float_position)) {
            button.setFillColor(sf::Color(255, 255, 255, 128));
        }

        else if (button2.getGlobalBounds().contains(float_position)) {
            button2.setFillColor(sf::Color(255, 255, 255, 128));
        }

        else if (button3.getGlobalBounds().contains(float_position)) {
            button3.setFillColor(sf::Color(255, 255, 255, 128));
        }
    }
    if (ev->type == sf::Event::MouseButtonReleased) {
        button.setFillColor(sf::Color(211, 78, 76));
        button2.setFillColor(sf::Color(211, 78, 76));
        button3.setFillColor(sf::Color(211, 78, 76));
    }

    window->draw(shape);

    window->draw(text);

    window->draw(text2);

    window->draw(button);

    window->draw(button2);

    window->draw(button3);

    window->draw(button1_text);

    window->draw(button2_text);

    window->draw(button3_text);
	
	//draw

	//select level, character

	//button play , press --> check selection

	//press--> state = PlayingState
}
