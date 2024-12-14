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
#include "PlayableCharacter.h"
#include "Observer.h"
#include "View.h"
#include "Stick.h"


void Block::updateGravity(){
    if (this->m_position.y < this->m_baseGround) {
        this->m_position.y += 5.f;
    }

    else {
        this->m_position.y = this->m_baseGround;
    }
}

bool Block::isMidAir(){
    return this->m_position.y < this->m_baseGround;
}

Block::Block(){}

Block::~Block(){
    
}

Block* Block::createBlock(const BlockType &type, const sf::Vector2f& position)
{
    Block* result = nullptr;

    switch (type)
    {
    case BlockType::ground:
    case BlockType::blue_ground:
        result = new Ground;
        result->interact = true;
        break;
    case BlockType::indestructible:
    case BlockType::blue_indestructible:
    case BlockType::dark_blue_indestructible:
        result = new IndestructibleBrick;
        result->interact = true;
        break;
    case BlockType::basebrick:
    case BlockType::blue_baseBrick:
    case BlockType::dark_blue_baseBrick:
    case BlockType::light_blue_baseBrick:
        result = new BaseBrick;
        result->interact = true;
        break;
    case BlockType::brick:
    case BlockType::blue_brick:
    case BlockType::light_blue_brick:
        result = new Brick;
        result->interact = true;
        break;
    case BlockType::vertical_pipe:
    case BlockType::vertical_pipe_top:
        result = new VerticalPipe;
        result->interact = true;
        break;
        //need animation
    case BlockType::bonus:
        result = new BonusBrick;
        result->interact = true;
        break;
    case BlockType::tree:
        result = new Tree;
        result->interact = false;
        break;
    case BlockType::mountain:
        result = new Mountain;
        result->interact = false;
        break;
    case BlockType::cloud:
    case BlockType::winter_cloud:
        result = new Cloud;
        result->interact = false;
        break;
    case BlockType::castle:
    case BlockType::big_castle:
        result = new Castle;
        result->interact = false;
        break;
    case BlockType::flag:
    case BlockType::winter_flag:
        result = new Flag;
        result->interact = true;
        break;
    case BlockType::stick:
    case BlockType::winter_stick:
        result = new Stick;
        result->interact = true;
        break;

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

        result->m_shape.setSize(sf::Vector2f(floatRect.width, floatRect.height));

        result->m_shape.setTexture(temp.first);
        
        result->m_shape.setTextureRect(temp.second);

        sf::Vector2f tempPos = position;

        if (type == BlockType::flag) {
            tempPos.x = tempPos.x - result->m_shape.getSize().x + 5.f;
        }
        
        tempPos.y -= temp.second.getSize().y;
        
        if (type == BlockType::vertical_pipe_top)
        {
            tempPos.x -= 4.f;
        }

        result->m_position = tempPos;
        
        result->m_baseGround = result->m_position.y;
        
        result->m_shape.setPosition(result->m_position);
        
        result->m_alive = true;

        result->m_delay_dead_time = 0;
    }
    
    return result;
}

void Block::die() {
    this->m_alive = false;
    this->m_delay_dead_time = -1;
}

bool Block::isDead() {
    return !this->m_alive;
}

void Block::draw(sf::RenderWindow* window) {

    window->draw(this->m_shape);
}

void Block::update(const float& deltaTime, const std::vector<Observer*>& observers) {
    this->twinkle(deltaTime);

    this->updateGravity();

    this->m_shape.setPosition(this->m_position);

    this->m_sprite.setPosition(this->m_position);
}

bool Block::standInView(View view){
    return view.containObjectAt(this->m_shape.getGlobalBounds());
}

bool Block::canInteract(){
    return this->interact;
}

void Block::jump(){
    this->m_position.y -= 10.f;
}

bool Block::connectToUnderground(){
    return false;
}

bool Block::connectToGround()
{
    return false;
}

bool Block::canKillPlayable(){
    return false;
}

void Block::twinkle(const float& deltaTime){}

void Block::hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers){
    sf::Vector2f newm_position;

    if (this->m_position.y < this->m_baseGround && character->beingHitFromAbove(this->m_shape.getGlobalBounds(),newm_position)) {
        character->die();
    }
}

void Block::hit(Item* item, const std::vector<Observer*>& observers){
    sf::Vector2f newPosition;

    if (((item->beingHitFromAbove(this->m_shape.getGlobalBounds(), newPosition))
        || (item->beingHitFromLeftBy(this->m_shape.getGlobalBounds(), newPosition))
        || (item->beingHitFromRightBy(this->m_shape.getGlobalBounds(), newPosition))) && this->isMidAir()) {

        item->beingCollectedByPlayable(observers);
    }
}

void Block::specificResultAfterBeingHitFromLeft(const std::vector<Observer*>& observers, const PlayableCharacter& character)
{
}

void Block::specificResultAfterBeingHitFromRight(const std::vector<Observer*>& observers, const PlayableCharacter& character)
{
}

void Block::specificResultAfterBeingHitFromBottom(const std::vector<Observer*>& observers, const PlayableCharacter& character)
{
}







