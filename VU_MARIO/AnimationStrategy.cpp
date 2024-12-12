#include "AnimationStrategy.h"


AnimationStrategy::AnimationStrategy(){
	texture = nullptr;
	curFrameNum = 0;
}

AnimationStrategy::AnimationStrategy(sf::Texture* texture, std::vector<sf::IntRect> frames, const float& SPF) : texture(texture), frames(frames),frameSize(frames.size()),SPF(SPF),curFrameNum(0){
	this->m_time_each_frame = 0.1;
}

AnimationStrategy::AnimationStrategy(AnimationStrategy& other) : texture(texture),frames(frames),frameSize(frames.size()),SPF(SPF), curFrameNum(0) {}

AnimationStrategy::~AnimationStrategy(){}

void AnimationStrategy::die(const float& deltaTime, sf::Sprite& sprite){
}

void AnimationStrategy::moveleft(const float& deltaTime, sf::Sprite& sprite)
{
}

void AnimationStrategy::moveright(const float& deltaTime, sf::Sprite& sprite)
{
}

void AnimationStrategy::changeAutomatically(const float& deltaTime, sf::Sprite& sprite)
{
}

void AnimationStrategy::jump(const float& deltaTime, sf::Sprite& sprite)
{
}


void AnimationStrategy::doNothing(sf::Sprite& sprite){
	this->curFrameNum = 0;
	this->setSprite(sprite);
}

void AnimationStrategy::setSprite(sf::Sprite& sprite){
	sprite.setTexture(*this->texture);
	sprite.setTextureRect(this->frames[this->curFrameNum]);
}

void AnimationStrategy::changeTexture(sf::Texture* texture, std::vector<sf::IntRect> frames){
	this->texture = texture;
	this->frames = frames;
	this->frameSize = frames.size();
}


