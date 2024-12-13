#pragma once
#include "Block.h"
class Observer;
class PlayableCharacter;

class Brick : public Block{
public:
    Brick();

    void jump() override;
    void specificResultAfterBeingHitFromBottom(const std::vector<Observer*>& observers, const PlayableCharacter& character) override;
};