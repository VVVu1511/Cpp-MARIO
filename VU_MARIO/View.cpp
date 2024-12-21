#include "View.h"
#include <iostream>

void View::setForAttributes(std::vector<sf::Text>& texts){
	int size = texts.size();

	for (int i = 0; i < size; i++) {
		texts[i].setPosition(texts[i].getPosition().x + view.getCenter().x - 600.f,texts[i].getPosition().y + view.getCenter().y - view.getSize().y / 2);
	}
}

View::View() {
	
}

View::View(sf::FloatRect floatRect) {
	view = sf::View(floatRect);
}

View::~View() {
	
}

void View::update(const std::vector<PlayableCharacter*>& playable, sf::RenderWindow* window){
	float minPositionX = std::numeric_limits<float>::max();
	PlayableCharacter* chosen_character = nullptr;

	for (PlayableCharacter* character : playable) {
		if (character != nullptr && character->canViewFollow() == true && character->findMinForView(minPositionX) == true) {
			chosen_character = character;
		}
	}
	
	/*if (minPositionX > view.getCenter().x && chosen_character != nullptr) {
		chosen_character->setCenterForView(view);
	}*/
	
	if(chosen_character != nullptr) chosen_character->setCenterForView(view,window);

	for (PlayableCharacter* character : playable) {
		character->standInsideView(view);
	}

}

void View::setForWindow(sf::RenderWindow* window){
	window->setView(view);
}

bool View::containObjectAt(const sf::FloatRect& bounds){
	sf::FloatRect m_bounds(
		view.getCenter().x - view.getSize().x / 2,
		view.getCenter().y - view.getSize().y / 2,
		view.getSize().x,
		view.getSize().y
	);

	if (bounds.left > m_bounds.left + m_bounds.width) return false;
	else if (bounds.left + bounds.width < m_bounds.left) return false;

	return true;
}
