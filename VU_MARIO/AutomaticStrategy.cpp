#include "AutomaticStrategy.h"


AutomaticStrategy::AutomaticStrategy() : AnimationStrategy(){}

AutomaticStrategy::AutomaticStrategy(sf::Texture* texture, std::vector<sf::IntRect> frames, const float& SPF) : AnimationStrategy(texture,frames,SPF){}

AutomaticStrategy::AutomaticStrategy(const AutomaticStrategy& other) : AnimationStrategy(other.texture,other.frames,other.SPF){}

void AutomaticStrategy::changeAutomatically(const float& deltaTime, sf::Sprite& sprite){
	int bound;
	
	if (frameSize == 4) bound = 1;
	else bound = 2;

	(curFrameNum < frameSize - bound) ? curFrameNum++ : curFrameNum = 0;
	
	this->setSprite(sprite);
}


AutomaticStrategy::~AutomaticStrategy(){}
