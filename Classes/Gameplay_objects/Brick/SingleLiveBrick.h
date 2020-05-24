#pragma once 

#include "cocos2d.h"
#include "Brick.h"
#include "Gameplay_objects/Bonus.h"

using SpritesVec_t = std::vector<cocos2d::Sprite*>;
using BonusesVec_t = std::vector<Bonus*>;

class SpeedUpBrick : public Brick {
private:
	BrickState state;
public:
	SpeedUpBrick(cocos2d::Node* parent);
	virtual void HandleCollision(Ball* ball) override;
	virtual BrickState GetState() const override;
};

class BonusBrick : public Brick {
private:
	BrickState state;
	cocos2d::Sprite* bonusIcon;
	BonusesVec_t* bonuses;
	void SpawnBonus();
public:
	BonusBrick(int brickColor, cocos2d::Node* parent, BonusesVec_t& gameBonuses);
	virtual void HandleCollision(Ball* ball) override;
	virtual BrickState GetState() const override;
};


