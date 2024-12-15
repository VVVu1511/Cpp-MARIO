#include "Item.h"
#include "Flower.h"
#include "Coin.h"
#include "Star.h"
#include "GoodMushroom.h"
#include "AutomaticStrategy.h"
#include "Animation.h"
#include "AssetManager.h"
#include "Block.h"
#include "Animation.h"
#include "View.h"

bool Item::isMidAir(){
    return this->m_position.y < this->m_baseGround - this->m_shape.getSize().y;
}

Item::Item(){}

Item::~Item(){}

Item* Item::createItem(const ItemType &type, const sf::Vector2f &position){
    Item* result = nullptr;

    switch (type)
    {
    case ItemType::flower:
        result = new Flower;
        break;
    case ItemType::star:
        result = new Star;
        break;
    case ItemType::mushroom:
        result = new GoodMushroom;
        break;
    case ItemType::coin:
        result = new Coin;
        break;
    default:
        result = nullptr;
        break;
    }

    if (result)
    {
        AssetManager* instance = AssetManager::getInstance();
        
        std::pair<sf::Texture*, std::vector<sf::IntRect>> temp = instance->getItem(type);
        
        sf::IntRect intRect = temp.second[0];

        sf::FloatRect floatRect(
            static_cast<float>(intRect.left),
            static_cast<float>(intRect.top),
            static_cast<float>(intRect.width),
            static_cast<float>(intRect.height)
        );


        result->m_shape.setSize(sf::Vector2f(floatRect.width, floatRect.height));

        result->m_sprite.setTexture(*temp.first);
        result->m_sprite.setTextureRect(intRect);

        result->m_animation.addStrategy({ new AutomaticStrategy(temp.first,temp.second,1.0 / 60)});

        sf::Vector2f tempPos = position;

        tempPos.y -= floatRect.getSize().y;

        result->m_position = tempPos;
        
        result->m_shape.setPosition(result->m_position);

        result->m_baseGround = result->m_position.y;

        result->m_alive = true;

        result->m_Vx = 3.f;

        result->m_delay_dead_time = 0;
    }
    
    return result;  
}

void Item::move(const float& deltaTime){
    this->m_position.x += m_Vx;
}

void Item::die(){
    this->m_alive = false;
    this->m_delay_dead_time = -1;
}

void Item::reset(){
    this->m_baseGround = std::numeric_limits<float>::max();
}

void Item::changeDirection(){
    this->m_Vx *= (-1);
}

bool Item::isDead()
{
    return !(this->m_alive);
}

void Item::update(const float& deltaTime,const std::vector<Observer*>& observers){
    this->twinkle(deltaTime);
    this->move(deltaTime);

    if (this->m_position.y < this->m_baseGround - this->m_shape.getSize().y) {
        this->m_position.y += 5.f;
    }
    else {
        this->m_position.y = this->m_baseGround - this->m_shape.getSize().y;
    }
    
    this->m_sprite.setPosition(this->m_position);
    this->m_shape.setPosition(this->m_position);
}

void Item::draw(sf::RenderWindow* window){
    window->draw(this->m_sprite);
}

void Item::twinkle(const float& deltaTime){
    m_animation.changeAutomatically(deltaTime, m_sprite);
}

bool Item::standInView(View view){
    return view.containObjectAt(this->m_shape.getGlobalBounds());
}

void Item::hit(Block* block){
    sf::Vector2f newPosition;

    if (block->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition) || block->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition)) {
        this->m_position = newPosition;
        this->changeDirection();
    }
}

void Item::beingCollectedByPlayable(PlayableCharacter* character,const std::vector<Observer*>& observers){
    this->die();
}

void Item::standOn(Block* block,const std::vector<Observer*>& observers){
    sf::Vector2f newPosition;

    if (block->underObjectAt(this->m_shape.getGlobalBounds(), newPosition)) {
        if (newPosition.y < this->m_baseGround) {
            this->m_baseGround = newPosition.y;
        }
    }
}


