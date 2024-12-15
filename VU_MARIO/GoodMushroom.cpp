#include "GoodMushroom.h"
#include "Observer.h"

GoodMushroom::GoodMushroom()
{
}

void GoodMushroom::beingCollectedByPlayable(PlayableCharacter* character,const std::vector<Observer*>& observers){
	//sound
	Item::beingCollectedByPlayable(character,observers);

	for (Observer* observer : observers) {
		observer->collectGoodMushroom(character);
	}
}
