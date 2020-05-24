#include "Paddle.h"
#include "Constants.h"

USING_NS_CC;

void Paddle::SetMoveLimitPosX(float gameFieldX, float gameFieldWidth) {
	leftLimitX = gameFieldX;
	rightLimitX = gameFieldX + gameFieldWidth;
}

Paddle::Paddle(cocos2d::Node* parent): state(PaddleState::SIMPLE) {
	sprite = Sprite::create(PADDLE_TEXTURE);
	sprite->setName("Paddle");
	float width = parent->getContentSize().width;
	float xPos = Director::getInstance()->getVisibleOrigin().x;
	SetMoveLimitPosX(xPos, width);
	movementDirection = 0;
	sprite->setAnchorPoint(Vec2(0.5f, 0.0f));
	sprite->setPosition(Vec2(width * 0.5f, 0));
	parent->addChild(sprite);
}

Paddle::~Paddle() {
	if (sprite != nullptr) {
		sprite->removeFromParentAndCleanup(true);
		sprite = nullptr;
	}
}

Rect Paddle::GetRect() const {
	return sprite->getBoundingBox();
}

Point Paddle::GetPosition() const {
	return sprite->getPosition();
}

void Paddle::SetMovement(int direction) {
	movementDirection = direction;
}
void Paddle::UpdateState() {
	auto rect = sprite->getBoundingBox();
	switch (movementDirection) {
	case -1:
		if (rect.getMinX() - PADDLE_VELOCITY < leftLimitX)
			sprite->setPositionX(leftLimitX + rect.size.width * 0.5f);
		else
			sprite->setPositionX(rect.getMidX() - PADDLE_VELOCITY);
		break;
	case 1:
		if (rect.getMaxX() + PADDLE_VELOCITY > rightLimitX)
			sprite->setPositionX(rightLimitX - rect.size.width * 0.5f);
		else
			sprite->setPositionX(rect.getMidX() + PADDLE_VELOCITY);
		break;
	case 0:
		break;
	}
}

int Paddle::GetMovement() {
	return movementDirection;
}

Paddle::PaddleState Paddle::GetState() const {
	return state;
}
void Paddle::SetState(PaddleState newState) {
	state = newState;
}