#pragma once
#include <SFML/Graphics.hpp>
#include "PlayableCharacter.h"
#include<vector>

class View {

private:
	sf::View view;
	
public:
	View();
	View(sf::FloatRect floatRect);
	~View();

	void setForAttributes(std::vector<sf::Text>& texts);
	void update(std::vector<PlayableCharacter*> playable,sf::RenderWindow* window);
	void setForWindow(sf::RenderWindow* window);
	bool containObjectAt(const sf::FloatRect& bounds);
};