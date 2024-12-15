#include "PlayableCharacterObserver.h"
#include "GameState.h"
#include "PlayableCharacter.h"

PlayableCharacterObserver::PlayableCharacterObserver(){}

void PlayableCharacterObserver::addPlayingState(PlayingState* gamestate)
{
}

void PlayableCharacterObserver::addPlayableCharacter(PlayableCharacter* character)
{
	if (character != nullptr) {
		this->characters.push_back(character);
	}
}

void PlayableCharacterObserver::killEnemies(){

}

void PlayableCharacterObserver::collectCoins(){}

void PlayableCharacterObserver::collectFlower(PlayableCharacter* character){
	
}

void PlayableCharacterObserver::collectGoodMushroom(PlayableCharacter* character){
	
}

void PlayableCharacterObserver::collectStar(PlayableCharacter* character){
	
}

void PlayableCharacterObserver::hitBonusBrick(const sf::Vector2f& position, ItemType type){}

void PlayableCharacterObserver::hitStick(){
}

void PlayableCharacterObserver::bossShooting(const sf::Vector2f& position, const float& speed){

}

void PlayableCharacterObserver::mainShooting(const sf::Vector2f& position, const float& speed){
	
}

void PlayableCharacterObserver::mainTurnToSmall(PlayableCharacter* character){

}


