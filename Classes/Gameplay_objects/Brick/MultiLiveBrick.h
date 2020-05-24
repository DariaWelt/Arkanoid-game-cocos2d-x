#pragma once 

#include "cocos2d.h"
#include "Brick.h"

using SpritesVec_t = std::vector<cocos2d::Sprite*>;

class MultiLiveBrick: public Brick {
public:
	MultiLiveBrick(int colorType, cocos2d::Node* parent, int healthPoints);
	virtual void HandleCollision(Ball* ball) override;
	virtual BrickState GetState() const override;
protected:
	int hp;
	SpritesVec_t hpSprites;
};
