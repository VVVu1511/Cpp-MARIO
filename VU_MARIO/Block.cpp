#include "Block.h"
#include "NonPlayableCharacter.h"
#include "Item.h"
#include "Ground.h"
#include "Brick.h"
#include "BonusBrick.h"
#include "HorizontalPipe.h"
#include "VerticalPipe.h"
#include "BaseBrick.h"
#include "Cloud.h"
#include "Castle.h"
#include "Flag.h"
#include "Tree.h"
#include "Mountain.h"
#include "IndestructibleBrick.h"
#include "AssetManager.h"
#include "AutomaticStrategy.h"
#include "Animation.h"
#include "Observer.h"
#include "View.h"
#include "Stick.h"

Block::Block(){}

Block::~Block(){
    
}

Block* Block::createBlock(BlockType type, sf::Vector2f position)
{
    Block* result = nullptr;

    switch (type)
    {
    case BlockType::ground:
        result = new Ground;
        break;
    case BlockType::indestructible:
        result = new IndestructibleBrick;
        break;
    case BlockType::basebrick:
        result = new BaseBrick;
        break;
    case BlockType::brick:
        result = new HorizontalPipe;
        break;
    case BlockType::vertical_pipe:
    case BlockType::vertical_pipe_top:
        result = new VerticalPipe;
        break;
        //need animation
    case BlockType::bonus:
        result = new BonusBrick;
        break;
    case BlockType::tree:
        result = new Tree;
        break;
    case BlockType::mountain:
        result = new Mountain;
        break;
    case BlockType::cloud:
        result = new Cloud;
        break;
    case BlockType::castle:
        result = new Castle;
        break;
    case BlockType::flag:
        result = new Flag;
        break;
    case BlockType::stick:
        result = new Stick;
    default:
        result = nullptr;
        break;
    }

    if (result)
    {
        AssetManager* instance = AssetManager::getInstance();

        std::pair<sf::Texture*, sf::IntRect> temp = instance->getBlock(type);

        sf::IntRect intRect = temp.second;

        sf::FloatRect floatRect(
            static_cast<float>(intRect.left),
            static_cast<float>(intRect.top),
            static_cast<float>(intRect.width),
            static_cast<float>(intRect.height)
        );

        result->shape.setSize(sf::Vector2f(floatRect.width, floatRect.height));

        result->shape.setTexture(temp.first);
        result->shape.setTextureRect(temp.second);

        position.y -= temp.second.getSize().y;
        
        result->position = position;
        
        result->baseGround = position.y;


        result->shape.setPosition(position);
    }
    
    return result;
}

void Block::die() {
    this->alive = false;
}

bool Block::isDead() {
    return !this->alive;
}

void Block::draw(sf::RenderWindow* window) {

    window->draw(this->shape);
}

void Block::update(const float& deltaTime, std::vector<Observer*>& observers) {
    this->twinkle(deltaTime);

    if (this->position.y < this->baseGround) {
        this->position.y += 5.f;
    }

    else {
        this->position.y = this->baseGround;
    }

    this->shape.setPosition(this->position);
}


bool Block::standInView(View view){
    return view.containObjectAt(this->shape.getGlobalBounds());
}

void Block::twinkle(const float& deltaTime){}


void Block::hit(NonPlayableCharacter* character, std::vector<Observer*>& observers){
    if (this->position.y < this->baseGround) {
        character->beingHitByBlock(this->shape.getGlobalBounds(),observers);
    }
}

void Block::hit(Item* item, std::vector<Observer*>& observers){
    item->beingCollectedByPlayable(this->shape.getGlobalBounds(), observers);
}

void Block::beingStoodOnByCharacter(float& baseGround, const sf::FloatRect& bounds) {
    sf::FloatRect m_bounds = shape.getGlobalBounds();
    
    if (bounds.left + bounds.width > m_bounds.left && bounds.left < m_bounds.left + m_bounds.width) {
        if (this->position.y >= bounds.top + 15.f && position.y < baseGround) {
            baseGround = this->position.y;
        }
    }
}

bool Block::beingHitByPlayable(const sf::FloatRect& bounds, sf::Vector2f& position, std::vector<Observer*>& observers) {
    sf::FloatRect m_bounds = shape.getGlobalBounds();

    if (bounds.intersects(m_bounds)) {
        if (bounds.left + bounds.width <= m_bounds.left + 5.f) {
            position.x = m_bounds.left - bounds.width;
        }
        
        else if (bounds.left >= m_bounds.left + m_bounds.width - 5.f) {
            position.x = m_bounds.left + m_bounds.width;
        }

        else {
            position.y = m_bounds.top + m_bounds.height;
        }
        return true;
        
    }
    return false;
}


bool Block::beingHitByNonPlayable(const sf::FloatRect& bounds, sf::Vector2f& position, std::vector<Observer*>& observers,float& speed){
    
    if (beingHitByPlayable(bounds, position,observers)) {
        speed *= -1.001;
        return true;
    }

    return false;
    
}
