#include "WorldObject.h"
#include<iostream>

bool WorldObject::beingHitFromBottom(const sf::FloatRect& bounds, sf::Vector2f& newPosition) const{
    sf::FloatRect m_bounds = this->m_shape.getGlobalBounds();

    if (bounds.intersects(m_bounds)) {
        if (bounds.top >= m_bounds.top + m_bounds.height - 10.f) {
            newPosition = sf::Vector2f(bounds.left,m_bounds.top + m_bounds.height);
            return true;
        }
    }

    return false;
}

bool WorldObject::beingHitFromLeftBy(const sf::FloatRect& bounds, sf::Vector2f& newPosition) const {
    sf::FloatRect m_bounds = this->m_shape.getGlobalBounds();

    if (bounds.intersects(m_bounds)) {
        float width = bounds.left + bounds.width;
        if (width <= m_bounds.left + 5.f) {
            newPosition = sf::Vector2f(m_bounds.left - bounds.width, bounds.top);
            return true;
        }        
    }

    return false;
}

bool WorldObject::beingHitFromRightBy(const sf::FloatRect& bounds, sf::Vector2f& newPosition) const {
    sf::FloatRect m_bounds = this->m_shape.getGlobalBounds();

    if (bounds.intersects(m_bounds)) {
        if(bounds.left >= m_bounds.left + m_bounds.width - 5.f) {
            newPosition = sf::Vector2f(m_bounds.left + m_bounds.width,bounds.top);
            return true;

        }
    }

    return false;
}

bool WorldObject::beingHitFromAbove(const sf::FloatRect& bounds, sf::Vector2f& newPosition) const {
    sf::FloatRect m_bounds = this->m_shape.getGlobalBounds();

    if (bounds.intersects(m_bounds)) {
        if (bounds.top + bounds.height <= this->m_position.y + 10.f) {
            newPosition = sf::Vector2f(bounds.left, m_bounds.top);
            
            return true;
        }
    }

    return false;
}

bool WorldObject::underObjectAt(const sf::FloatRect& bounds, sf::Vector2f& newPosition) const {
    
    sf::FloatRect m_bounds = this->m_shape.getGlobalBounds();

    if (bounds.left + bounds.width > m_bounds.left && bounds.left < m_bounds.left + m_bounds.width) {
        if (this->m_position.y >= bounds.top + 15.f) {
            newPosition = sf::Vector2f(this->m_position.x, this->m_position.y);
            return true;
        }
    }


    return false;
}

bool WorldObject::canBeDeleted() const {
    return this->m_delay_dead_time < 0;
}

bool WorldObject::canBeDeletedWhenOutOfView() const
{
    return false;
}
