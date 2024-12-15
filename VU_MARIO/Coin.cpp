#include "Coin.h"
#include "Observer.h"

Coin::Coin()
{
}

void Coin::beingCollectedByPlayable(PlayableCharacter* character,const std::vector<Observer*>& observers){
	Item::beingCollectedByPlayable(character,observers);

	for (Observer* observer : observers) {
		observer->collectCoins();
	}
}

void Coin::move(const float& deltaTime){

}

void Coin::standOn(Block* block, const std::vector<Observer*>& observers){

}

void Coin::reset(){

}

