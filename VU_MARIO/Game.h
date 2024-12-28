#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class GameState;
class Observer;
enum class StateOfGame;

class Game {
private:
    sf::RenderWindow* window;
    sf::Event* ev;
    sf::Font font;
    GameState* currentState;
    std::vector<Observer*> observers;
    sf::Clock clock;
    float deltaTime;


public:
    Game();
    ~Game();
    void run();
    void chooseState();
};
