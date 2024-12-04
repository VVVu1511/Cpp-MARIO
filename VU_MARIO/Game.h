#pragma once
#include <SFML/Graphics.hpp>

class GameState;
class Observer;
enum class StateOfGame;

class Game {
private:
	sf::Clock clock;
	float deltaTime;
	sf::RenderWindow* window;
	sf::Event* ev;
	GameState* currentState;
	std::vector<Observer*>observers;
	sf::Font font;
	StateOfGame state;

	void chooseState();
public:
	Game();
	
	void run();
	~Game();
};