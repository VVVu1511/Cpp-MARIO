#include "Game.h"
#include "MenuState.h"
#include "PlayingState.h"
#include <iostream>

void Game::run(){
	
    
    window = new sf::RenderWindow(sf::VideoMode(1200,576), "MARIO BROS 1985!");
	
    window->setFramerateLimit(60);

    if (!this->font.loadFromFile("../fonts/SuperMario256.ttf")) {
        std::cout << "Can not load file!";
    }

    this->currentState = new PlayingState;

    ev = new sf::Event;
	
    while (window->isOpen()) {
        while (window->pollEvent(*ev)) {
            if (ev->type == sf::Event::Closed) {
                window->close();
            }
            if (ev->type == sf::Event::KeyPressed) {
                if (ev->key.code == sf::Keyboard::Escape) {
                    window->close();
                }
            }
        }

        deltaTime = clock.restart().asSeconds();


        window->clear(sf::Color(92,148,252));
        this->currentState->execute(this->window,this->observers,this->currentState,this->deltaTime,this->ev,this->font);
        window->display();
    }
}

Game::~Game(){
	delete this->currentState;
	delete this->window;
	delete this->ev;
}
