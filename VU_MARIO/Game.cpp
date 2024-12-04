#include "Game.h"
#include "GameState.h"
#include "MenuState.h"
#include "PlayingState.h"
#include <iostream>

void Game::chooseState(){
    
    if (currentState != nullptr) {
        if (currentState->isActive()) return;

        delete currentState;
        currentState = nullptr;

        switch (state) {
        case StateOfGame::menu:
            state = StateOfGame::playing;
            break;
        case StateOfGame::playing:
            state = StateOfGame::menu;
            break;
        }
    }

    switch (state) {
    case StateOfGame::menu:
        currentState = new MenuState;
        break;
    case StateOfGame::playing:
        currentState = new PlayingState;
        break;
        /*case StateOfGame::changingMap:
            currentState = new MenuState;
            break;
        case StateOfGame::gameover:
            currentState = new MenuState;
            break;
        }*/
    }

}

Game::Game(){
    currentState = nullptr;
    state = StateOfGame::playing;
}

void Game::run(){
	
    window = new sf::RenderWindow(sf::VideoMode(1200,576), "MARIO BROS 1985!");
	
    window->setFramerateLimit(60);

    if (!this->font.loadFromFile("../fonts/SuperMario256.ttf")) {
        std::cout << "Can not load file!";
    }

    

    ev = new sf::Event;
	
    while (window->isOpen()) {
        
        this->chooseState();

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

        deltaTime = clock.restart().asSeconds() * 30;

        window->clear(sf::Color(92,148,252));
        
        this->currentState->execute(window, observers, currentState, deltaTime, ev, font);

        window->display();
    }
}

Game::~Game(){
	delete this->currentState;
	delete this->window;
	delete this->ev;
}
