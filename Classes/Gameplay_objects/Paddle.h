#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Paddle {
public:

	enum class PaddleState {
		SIMPLE,
		MAGNETED
	};

	Paddle(cocos2d::Node* parent);
	~Paddle();
	void SetMoveLimitPosX(float gameFieldX, float gameFieldWidth);
	void SetMovement(int direction);
	cocos2d::Rect GetRect() const;
	int GetMovement();
	void UpdateState();
	PaddleState GetState() const;
	void SetState(PaddleState newState);
	cocos2d::Point GetPosition() const;
private:
	float leftLimitX;
	float rightLimitX;
	cocos2d::Sprite* sprite;
	int movementDirection;
	PaddleState state;
};
