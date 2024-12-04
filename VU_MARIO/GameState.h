#pragma once
#include<SFML/Graphics.hpp>


class Observer;

class GameState{

protected:
	bool active = false;
public:
	GameState();
	virtual ~GameState() = default;
	virtual void execute(sf::RenderWindow* window,std::vector<Observer*>&observers,GameState* gameState, const float& deltaTime, const sf::Event* ev,const sf::Font& font) = 0;
	virtual bool isActive() = 0;
};

