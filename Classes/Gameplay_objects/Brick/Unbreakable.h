#pragma once 

#include "cocos2d.h"
#include "Brick.h"

class Unbreakable: public Brick {
public:
	Unbreakable(cocos2d::Node* parent);
	virtual void HandleCollision(Ball* ball) override;
	virtual BrickState GetState() const override;
};

