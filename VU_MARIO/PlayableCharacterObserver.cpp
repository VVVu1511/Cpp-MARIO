#include "PlayableCharacterObserver.h"
#include "GameState.h"
#include "PlayableCharacter.h"

PlayableCharacterObserver::PlayableCharacterObserver(){}


void PlayableCharacterObserver::addPlayingState(PlayingState* gamestate)
{
}

void PlayableCharacterObserver::addPlayableCharacter(PlayableCharacter* character)
{
	this->characters.push_back(character);
}

void PlayableCharacterObserver::killEnemies(){

}

void PlayableCharacterObserver::collectCoins(){}

void PlayableCharacterObserver::collectFlower(){
	for (PlayableCharacter* character : characters) {
		character->collectFlower();
	}
}

void PlayableCharacterObserver::collectGoodMushroom(){
	for (PlayableCharacter* character : characters) {
		character->collectGoodMushroom();
	}
}

void PlayableCharacterObserver::collectStar(){
	for (PlayableCharacter* character : characters) {
		character->collectStar();
	}
}

void PlayableCharacterObserver::hitBonusBrick(const sf::Vector2f& position, ItemType type){}

void PlayableCharacterObserver::hitStick(){
}


