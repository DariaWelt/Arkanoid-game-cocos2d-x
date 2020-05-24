#pragma once 

#include "cocos2d.h"
#include "Gameplay_objects/Ball.h"
#include "Gameplay_objects/Paddle.h"

using BallsVec_t = std::vector<Ball*>;

class Bonus {
public:
	Bonus(int bonusType, cocos2d::Node* parent, cocos2d::Point position);
	~Bonus();
	virtual void Activate(BallsVec_t& balls, Paddle* paddle) = 0;
	bool MovingIsDone() const;
	cocos2d::Rect GetRect() const;
protected:
	cocos2d::Sprite* sprite;
	int typeID;
	bool isActivated;
private:
	void LoadIcon();
};


class NewBallBonus : public Bonus {
public:
	NewBallBonus(cocos2d::Node* parent, cocos2d::Point position);
	virtual void Activate(BallsVec_t& balls, Paddle* paddle) override;
};

class MagnetBonus : public Bonus {
public:
	MagnetBonus(cocos2d::Node* parent, cocos2d::Point position);
	virtual void Activate(BallsVec_t& balls, Paddle* paddle) override;
};

class ShildBonus : public Bonus {
public:
	ShildBonus(cocos2d::Node* parent, cocos2d::Point position);
	virtual void Activate(BallsVec_t& balls, Paddle* paddle) override;
};

class RandTrajectoryBonus : public Bonus {
public:
	RandTrajectoryBonus(cocos2d::Node* parent, cocos2d::Point position);
	virtual void Activate(BallsVec_t& balls, Paddle* paddle) override;
};

class SpeedDownBonus : public Bonus {
public:
	SpeedDownBonus(cocos2d::Node* parent, cocos2d::Point position);
	virtual void Activate(BallsVec_t& balls, Paddle* paddle) override;
};

class ExtendPaddleBonus : public Bonus {
public:
	ExtendPaddleBonus(cocos2d::Node* parent, cocos2d::Point position);
	virtual void Activate(BallsVec_t& balls, Paddle* paddle) override;
};