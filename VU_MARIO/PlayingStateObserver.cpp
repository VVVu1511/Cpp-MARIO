#include "PlayingStateObserver.h"
#include "PlayingState.h"

PlayingStateObserver::PlayingStateObserver(){}

void PlayingStateObserver::addPlayableCharacter(PlayableCharacter* character)
{
}

void PlayingStateObserver::addPlayingState(PlayingState* gamestate){
	this->GameStates.push_back(gamestate);
}

void PlayingStateObserver::killEnemies(){
	for (PlayingState* gameState : GameStates) {
		gameState->addScore(100);
	}
}

void PlayingStateObserver::collectCoins(){
	for (PlayingState* gameState : GameStates) {
		gameState->addCoin();
	}
}

void PlayingStateObserver::collectFlower(){
	
}

void PlayingStateObserver::collectGoodMushroom(){
	
}

void PlayingStateObserver::collectStar(){

}

void PlayingStateObserver::hitBonusBrick(const sf::Vector2f& position, ItemType type) {
	for (PlayingState* gameState : GameStates) {
		gameState->hitBonusBrick(position,type);
	}
}

void PlayingStateObserver::hitStick(){
	for (PlayingState* gameState : GameStates) {
		gameState->changeMap();
	}
}

void PlayingStateObserver::bossShooting(const sf::Vector2f& position, const float& speed){
	for (PlayingState* gameState : GameStates) {
		/*gameState->bossShootingEvent(position,speed);*/
	}
}

void PlayingStateObserver::mainShooting(const sf::Vector2f& position, const float& speed){


}
