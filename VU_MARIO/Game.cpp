#include "Game.h"
#include "GameState.h"
#include "MenuState.h"
#include "PlayingState.h"
#include "AssetManager.h"
#include <iostream>
#include "GameOverState.h"
#include "LogInState.h"

void Game::chooseState(){
    StateOfGame nextState = StateOfGame::playing;

    std::pair<int, PlayableCharacterType> mapAndmainCharacter;

    if (this->state == StateOfGame::menu) {
        mapAndmainCharacter = this->currentState->giveMapNumAndCharacterType();
    }

    if (currentState != nullptr) {
        if (currentState->isActive()) return;

        nextState = currentState->nextState();
        
        delete currentState;

        currentState = nullptr;
    }

    switch (nextState) {
    case StateOfGame::login:
        currentState = new LogInState(this->window, this->font);
        this->state = StateOfGame::login;
        break;

    case StateOfGame::menu:
        currentState = new MenuState(this->window,this->font);
        this->state = StateOfGame::menu;
        break;

    case StateOfGame::playing:
        currentState = new PlayingState;
        this->state = StateOfGame::playing;
        break;

    case StateOfGame::gameover:
        currentState = new GameOverState;
        this->state = StateOfGame::gameover;
        break;
    }
}

Game::Game(){
    currentState = nullptr;
    this->state = StateOfGame::playing;
}

void Game::run(){
	
    window = new sf::RenderWindow(sf::VideoMode(1200,576), "MARIO BROS 1985!");
	
    if (!this->font.loadFromFile("../fonts/VeniteAdoremus-rgRBA.ttf")) {
        std::cout << "Can not load file!";
    }

    ev = new sf::Event;
    window->setFramerateLimit(60);
	
    AssetManager::getInstance();

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

        deltaTime = clock.restart().asSeconds();
       
        window->clear(sf::Color(92,148,252));
        
        this->currentState->execute(window, observers, currentState, deltaTime, ev, font);

        window->display();
    }

    AssetManager::destroy();
}

Game::~Game(){
	delete this->currentState;
	delete this->window;
	delete this->ev;
}
