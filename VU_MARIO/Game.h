#pragma once
#include <SFML/Graphics.hpp>

class GameState;
class Observer;

class Game {
private:
	sf::Clock clock;
	float deltaTime;
	sf::RenderWindow* window;
	sf::Event* ev;
	GameState* currentState;
	std::vector<Observer*>observers;

public:
	void run();
	~Game();
};