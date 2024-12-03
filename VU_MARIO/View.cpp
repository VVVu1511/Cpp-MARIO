#include "View.h"
#include <iostream>

View::View() {
	
}

View::View(sf::FloatRect floatRect) {
	view = sf::View(floatRect);
}

View::~View() {
	
}

void View::update(std::vector<PlayableCharacter*> playable, sf::RenderWindow* window){
	float minPositionX = std::numeric_limits<float>::max();
	PlayableCharacter* chosen_character = nullptr;

	for (PlayableCharacter* character : playable) {
		if (character->findMinForView(minPositionX)) {
			chosen_character = character;
		}
	}
	
	if (minPositionX > view.getCenter().x && chosen_character != nullptr) {
		chosen_character->setCenterForView(view);
	}

	for (PlayableCharacter* character : playable) {
		character->standInView(view);
	}

}

void View::setForWindow(sf::RenderWindow* window){
	window->setView(view);
}

bool View::containObjectAt(const sf::Vector2f& position){
	sf::FloatRect bounds(
		view.getCenter().x - view.getSize().x / 2,
		view.getCenter().y - view.getSize().y / 2,
		view.getSize().x,
		view.getSize().y
	);

	return bounds.contains(position);
}
