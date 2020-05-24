#pragma once 

#include "cocos2d.h"
#include "Gameplay_objects/Ball.h"

class Brick {
public:
	enum class BrickState {
		ALIVE,
		BROKEN
	};

	Brick(int brickType, cocos2d::Node* parent);
	~Brick();
	
	virtual void HandleCollision(Ball* ball) = 0;
	void SetScale(float scale);
	void SetPosition(cocos2d::Point position);
	cocos2d::Point GetPosition() const;
	cocos2d::Rect GetRect() const;
	virtual BrickState GetState() const = 0;
	int GetType() const;

protected:
	void LoadIcon();

	cocos2d::Sprite* sprite;
	int typeID;
};