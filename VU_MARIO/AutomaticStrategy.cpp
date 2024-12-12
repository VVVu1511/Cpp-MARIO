#include "AutomaticStrategy.h"


AutomaticStrategy::AutomaticStrategy() : AnimationStrategy(){}

AutomaticStrategy::AutomaticStrategy(sf::Texture* texture, std::vector<sf::IntRect> frames, const float& SPF) : AnimationStrategy(texture,frames,SPF){
	if (frameSize == 4 || frameSize == 2) m_bound = 1;

	else m_bound = 2;
}

AutomaticStrategy::AutomaticStrategy(const AutomaticStrategy& other) : AnimationStrategy(other.texture,other.frames,other.SPF){}

void AutomaticStrategy::changeAutomatically(const float& deltaTime, sf::Sprite& sprite){
	if (this->m_time_each_frame > 0) {
		this->m_time_each_frame -= deltaTime;
		return;
	}

	(curFrameNum < frameSize - m_bound) ? curFrameNum++ : curFrameNum = 0;
	
	this->setSprite(sprite);
	this->m_time_each_frame = 0.2;
}

AutomaticStrategy::~AutomaticStrategy(){}
