#include "Game.h"
#include "GameState.h"
#include "MenuState.h"
#include "PlayingState.h"
#include "AssetManager.h"
#include <iostream>
#include "GameOverState.h"
#include "LogInState.h"

void Game::chooseState(){
    
    if (this->currentState->isActive() == true) return;

    GameState* temp = this->currentState;
    this->currentState = this->currentState->nextState();

    delete temp;
}

Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(1200, 576), "MARIO BROS 1985!");
    ev = new sf::Event;

    if (!this->font.loadFromFile("../fonts/VeniteAdoremus-rgRBA.ttf")) {
        std::cout << "Can not load file!";
    }

    this->currentState = new LogInState(window,font);
}

void Game::run(){
    AssetManager::getInstance();
    
    window->setFramerateLimit(60);

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
        
        this->chooseState();
 
        this->currentState->execute(window, observers, currentState, deltaTime, ev, font);

        window->display();
    }

    AssetManager::destroy();
}

Game::~Game(){
	delete this->currentState;
	delete this->window;
	delete this->ev;

    for (Observer* observer : observers) {
        delete observer;
    }
    observers.clear();
}
