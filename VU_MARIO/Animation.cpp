#include "Animation.h"
#include <iostream>

Animation::Animation(){}

Animation::Animation(std::vector<AnimationStrategy*> animation_strategies){
	this->strategies = animation_strategies;
}

Animation::Animation(Animation& other){
	for (int i = 0; i < other.strategies.size(); i++) {
		AnimationStrategy* newStrategy = new AnimationStrategy;
		*newStrategy = *other.strategies[i];
		this->strategies.push_back(newStrategy);
	}
}

Animation::~Animation(){
	for (AnimationStrategy* strategy : this->strategies) {
		delete strategy;
	}
}

void Animation::addStrategy(AnimationStrategy* animationStrategy){
	this->strategies.push_back(animationStrategy);
}

void Animation::die(const float& deltaTime, sf::Sprite& sprite){
	for (AnimationStrategy* strategy : strategies) {
		strategy->die(deltaTime,sprite);
	}
}

void Animation::moveleft(const float& deltaTime, sf::Sprite& sprite){
	for (AnimationStrategy* strategy : strategies) {
		strategy->moveleft(deltaTime, sprite);
	}
}

void Animation::moveright(const float& deltaTime, sf::Sprite& sprite){
	for (AnimationStrategy* strategy : strategies) {
		strategy->moveright(deltaTime, sprite);
	}
}

void Animation::changeAutomatically(const float& deltaTime, sf::Sprite& sprite){
	for (AnimationStrategy* strategy : strategies) {
		strategy->changeAutomatically(deltaTime, sprite);
	}
}

void Animation::jump(const float& deltaTime, sf::Sprite& sprite){
	for (AnimationStrategy* strategy : strategies) {
		strategy->jump(deltaTime, sprite);
	}
}

void Animation::doNothing(sf::Sprite& sprite){
	for (AnimationStrategy* strategy : strategies) {
		strategy->doNothing(sprite);
	}
}



