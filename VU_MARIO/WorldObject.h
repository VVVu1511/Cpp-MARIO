#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include<bitset>

class WorldObject{
protected:
	sf::RectangleShape m_shape;
	sf::Vector2f m_position;
	sf::Sprite m_sprite;
	bool m_alive;
	float m_baseGround;
	Animation m_animation;
	float m_delay_dead_time;

public:
	virtual bool beingHitFromBottom(const sf::FloatRect& bounds, sf::Vector2f& newPosition);
	virtual bool beingHitFromLeftBy(const sf::FloatRect& bounds, sf::Vector2f& newPosition);
	virtual bool beingHitFromRightBy(const sf::FloatRect& bounds, sf::Vector2f& newPosition);
	virtual bool beingHitFromAbove(const sf::FloatRect& bounds, sf::Vector2f& newPosition);
	virtual bool underObjectAt(const sf::FloatRect& bounds, sf::Vector2f& newPosition);
	virtual bool canBeDeleted();
};

