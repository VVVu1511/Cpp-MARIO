#pragma once
#include "Block.h"
class Observer;

class Brick : public Block{
public:
    Brick();

    void jump() override;
    void beingHitFromBottomByBigMario(const std::vector<Observer*>& observers) override;
};