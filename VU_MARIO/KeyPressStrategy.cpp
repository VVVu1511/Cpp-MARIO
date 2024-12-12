#include "KeyPressStrategy.h"


KeyPressStrategy::KeyPressStrategy() : AnimationStrategy(){}

KeyPressStrategy::KeyPressStrategy(sf::Texture* texture, std::vector<sf::IntRect> frames, const float& SPF) : AnimationStrategy(texture, frames, SPF) {
	switch (frameSize)
	{
	case 5:
	case 6:
		bound = 3;
		startOfMoving = 1;
		break;
	case 3:
		bound = 1;
		startOfMoving = 0;
		break;
	default:
		break;
	}
}

KeyPressStrategy::KeyPressStrategy(const KeyPressStrategy& other) : AnimationStrategy(other.texture,other.frames,other.SPF){}


void KeyPressStrategy::moveleft(const float& deltaTime, sf::Sprite& sprite){
	if (m_time_each_frame > 0) {
		m_time_each_frame -= deltaTime;
		return;
	}


	if (curFrameNum < bound) {
		curFrameNum++;
	}

	else curFrameNum = startOfMoving;
	
	sprite.setScale(-1.f, 1.f);
	this->setSprite(sprite);
	this->m_time_each_frame = 0.1;
}

void KeyPressStrategy::moveright(const float& deltaTime, sf::Sprite& sprite){
	if (m_time_each_frame > 0) {
		m_time_each_frame -= deltaTime;
		return;
	}

	if (curFrameNum < frameSize - 3) {
		curFrameNum++;
	}

	else curFrameNum = startOfMoving;
	
	sprite.setScale(1.f, 1.f);
	this->setSprite(sprite);

	this->m_time_each_frame = 0.1;
}


void KeyPressStrategy::jump(const float& deltaTime, sf::Sprite& sprite){
	
	curFrameNum = frameSize - 2;
	
	this->setSprite(sprite);
}



KeyPressStrategy::~KeyPressStrategy(){}


