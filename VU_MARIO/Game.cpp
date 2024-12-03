#include "Game.h"
#include "MenuState.h"
#include "PlayingState.h"

void Game::run(){
	
    
    window = new sf::RenderWindow(sf::VideoMode(1200,576), "MARIO BROS 1985!");
	
    window->setFramerateLimit(60);

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
        this->currentState->execute(window,this->observers,this->currentState,deltaTime,ev);
        window->display();
    }
}

Game::~Game(){
	delete this->currentState;
	delete this->window;
	delete this->ev;
}
