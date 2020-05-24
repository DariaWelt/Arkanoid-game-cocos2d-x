#pragma once

#include "cocos2d.h"

class Ball {
public:

	enum class BallState {
		CAPTURED,
		FREE,
		COLLIDED
	};

	Ball(cocos2d::Node* parent);
	Ball(const Ball& ball);
	~Ball();
	Ball& operator=(const Ball& ball);
	void ChangeVelocity(float deltaVelocity);
	void SetAngle(float angle);
	void ChangePosition(float dx, float dy);
	float GetAngle() const;
	void UpdatePosition(float dt);
	cocos2d::Rect GetRect() const;
	void SetState(BallState state);
	BallState GetState() const;
	cocos2d::Point GetPosition() const;
	bool IsGrabbled() const;
private:
	cocos2d::Sprite* sprite;
	float angle;
	float velocity;
	BallState ballState;
	cocos2d::Node* gameField;
};