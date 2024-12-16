#pragma once
#include "PlayableCharacter.h"

class GoodBullet : public PlayableCharacter{
private:
	
public:
	GoodBullet();
	void hit(NonPlayableCharacter* character, const std::vector<Observer*>& observers);
	bool canBeKilledByNonPlayable() override;

	void setCenterForView(sf::View& view,sf::RenderWindow* window) override;
	void move(const float& deltaTime) override;
	void update(const float& deltaTime, const std::vector<Observer*>& observers) override;
	bool findMinForView(float& minX) override;
	void standInsideView(sf::View& view) override;
	void changeDirection() override;
	bool canViewFollow() const override;
	
	void collect(Item* item, const std::vector<Observer*>& observers) override;
};

