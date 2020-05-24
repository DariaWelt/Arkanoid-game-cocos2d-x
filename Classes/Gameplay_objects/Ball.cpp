#include "Ball.h"
#include "Constants.h"
#include <cmath>

USING_NS_CC;

Ball::Ball(cocos2d::Node* parent): ballState(BallState::CAPTURED),
					angle(std::_Pi / 3), gameField(parent), velocity(BALL_VELOCITY) {

	auto paddle = gameField->getChildByName("Paddle");
	auto pinfo = AutoPolygon::generatePolygon(BALL_TEXTURE);
	sprite = Sprite::create(pinfo);
	paddle->addChild(sprite);
	sprite->setPosition(paddle->getContentSize().width * 0.5f, paddle->getContentSize().height * 1.3f);
}

Ball::Ball(const Ball& ball) {
	sprite->removeFromParentAndCleanup(true);
	sprite = ball.sprite;
	angle = ball.angle;
	velocity = ball.velocity;
	ballState = ball.GetState();
	gameField = ball.gameField;
} 

Ball::~Ball() {
	if (sprite != nullptr) {
		sprite->removeFromParentAndCleanup(true);
		sprite = nullptr;
	}
}

Ball& Ball::operator=(const Ball& ball) {
	sprite->removeFromParentAndCleanup(true);
	sprite = ball.sprite;
	angle = ball.angle;
	velocity = ball.velocity;
	ballState = ball.GetState();
	gameField = ball.gameField;
	return *this;
}

void Ball::ChangeVelocity(float deltaVelocity) {
	velocity += deltaVelocity;
}

void Ball::SetAngle(float newAngle) {
	if (ballState == BallState::COLLIDED)
		return;
	angle = newAngle;
	while (angle < 0) {
		angle += 2 * std::_Pi;
	}
	while (angle > 2 * std::_Pi) {
		angle -= 2 * std::_Pi;
	}

	if (ballState != BallState::CAPTURED)
		ballState = BallState::COLLIDED;
}

float Ball::GetAngle() const {
	return angle;
}

Rect Ball::GetRect() const {
	return sprite->getBoundingBox();
}

Point Ball::GetPosition() const {
	if (this->IsGrabbled()) {
		auto paddle = sprite->getParent();
		float y = sprite->getPositionY();
		float x = sprite->getPositionX() + paddle->getPositionX() - paddle->getContentSize().width * 0.5;
		return Vec2(x, y);
	}
	else
		return sprite->getPosition();
}

bool Ball::IsGrabbled() const {
	return sprite->getParent() != gameField;
}

void Ball::UpdatePosition(float dt) {	
	if (ballState == BallState::FREE || ballState == BallState::COLLIDED) {
		float dx = velocity * dt * cos(angle);
		float dy = velocity * dt * sin(angle);
		ChangePosition(dx, dy);
		ballState = BallState::FREE;
	}
}

void Ball::SetState(BallState state) {
	ballState = state;
	auto paddle = gameField->getChildByName("Paddle");
	sprite->retain();
	sprite->removeFromParent();
	if (ballState == BallState::FREE) {
		gameField->addChild(sprite);
		sprite->setPositionX(sprite->getPositionX() + paddle->getPositionX() - paddle->getContentSize().width * 0.5);
	}
	else {
		gameField->getChildByName("Paddle")->addChild(sprite);
		sprite->setPositionX(sprite->getPositionX() - paddle->getPositionX() + paddle->getContentSize().width * 0.5);
	}
	sprite->release();
}

void Ball::ChangePosition(float dx, float dy) {
	sprite->setPosition(sprite->getPositionX() + dx, sprite->getPositionY() + dy);
}

Ball::BallState Ball::GetState() const {
	return ballState;
}