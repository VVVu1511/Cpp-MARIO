#include <SFML/Graphics.hpp>
#include "PlayableCharacter.h"

class View {
private:
	sf::View view;
public:
	View();
	View(sf::FloatRect floatRect);
	~View();

	void update(std::vector<PlayableCharacter*> playable,sf::RenderWindow* window);
	void setForWindow(sf::RenderWindow* window);
	bool containObjectAt(const sf::Vector2f& position);
};