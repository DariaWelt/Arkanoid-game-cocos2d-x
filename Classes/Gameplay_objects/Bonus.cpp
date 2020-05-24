#include "Bonus.h"
#include "Constants.h"

USING_NS_CC;

Bonus::Bonus(int bonusType, cocos2d::Node* parent, Point position): typeID(bonusType), sprite(nullptr), isActivated(false) {
	LoadIcon();
	parent->addChild(sprite);
	sprite->setPosition(position);
	sprite->setScale(0.2f);
	float targetPos = parent->getBoundingBox().getMinY() + 3;
	float time = abs(position.y - targetPos) / BONUS_VELOCITY;
	auto moveTo = MoveTo::create(time, Vec2(position.x, targetPos));
	moveTo->setTag(99);
	sprite->runAction(moveTo);
}

bool Bonus::MovingIsDone() const {
	auto action = sprite->getActionByTag(99);
	if (action == nullptr || action->isDone())
		return true;
	return false;
}

Rect Bonus::GetRect() const {
	return sprite->getBoundingBox();
}

Bonus::~Bonus(){
	if (sprite != nullptr) {
		sprite->removeFromParentAndCleanup(true);
		sprite = nullptr;
	}
}

void Bonus::LoadIcon() {
	if (sprite != nullptr) {
		sprite->removeFromParentAndCleanup(true);
		sprite = nullptr;
	}
	PolygonInfo pinfo;
	switch (typeID) {
	case BONUS_TYPE_RESIZE_PADDLE:
		pinfo = AutoPolygon::generatePolygon(BONUS_ATLAS, Rect(BONUS_SIZE * 0, BONUS_SIZE * 0, BONUS_SIZE, BONUS_SIZE));
		break;
	case BONUS_TYPE_RAND_TRAGECTORY:
		pinfo = AutoPolygon::generatePolygon(BONUS_ATLAS, Rect(BONUS_SIZE * 2.0f, BONUS_SIZE * 0, BONUS_SIZE, BONUS_SIZE));
		break;
	case BONUS_TYPE_NEW_BALL:
		pinfo = AutoPolygon::generatePolygon(BONUS_ATLAS, Rect(BONUS_SIZE * 1.0f, BONUS_SIZE * 0, BONUS_SIZE, BONUS_SIZE));
		break;
	case BONUS_TYPE_MAGNET:
		pinfo = AutoPolygon::generatePolygon(BONUS_ATLAS, Rect(BONUS_SIZE * 1.0f, BONUS_SIZE * 1.0f, BONUS_SIZE, BONUS_SIZE));
		break;
	case BONUS_TYPE_SHILD:
		pinfo = AutoPolygon::generatePolygon(BONUS_ATLAS, Rect(BONUS_SIZE * 0, BONUS_SIZE * 1.0f, BONUS_SIZE, BONUS_SIZE));
		break;
	case BONUS_TYPE_BALL_SPEED_DOWN:
		pinfo = AutoPolygon::generatePolygon(BONUS_ATLAS, Rect(BONUS_SIZE * 2.0f, BONUS_SIZE * 1.0f, BONUS_SIZE, BONUS_SIZE));
		break;
	}
	sprite = Sprite::create(pinfo);
}

NewBallBonus::NewBallBonus(cocos2d::Node* parent, Point position): Bonus(BONUS_TYPE_NEW_BALL, parent, position){}

void NewBallBonus::Activate(BallsVec_t& balls, Paddle* paddle){
	if (isActivated)
		return;
	balls.push_back(new Ball(sprite->getParent()));
	isActivated = true;
}

MagnetBonus::MagnetBonus(cocos2d::Node* parent, Point position): Bonus(BONUS_TYPE_MAGNET, parent, position) {}

void MagnetBonus::Activate(BallsVec_t& balls, Paddle* paddle){
	if (isActivated)
		return;
	paddle->SetState(Paddle::PaddleState::MAGNETED);
	isActivated = true;
}

ShildBonus::ShildBonus(cocos2d::Node* parent, Point position) : Bonus(BONUS_TYPE_SHILD, parent, position) {}

void ShildBonus::Activate(BallsVec_t& balls, Paddle* paddle){
	if (isActivated)
		return;
	auto gameField = sprite->getParent();
	(gameField->getChildByName("Bottom"))->setOpacity(100);
	isActivated = true;
}

RandTrajectoryBonus::RandTrajectoryBonus(cocos2d::Node* parent, Point position) : Bonus(BONUS_TYPE_RAND_TRAGECTORY, parent, position) {}

void RandTrajectoryBonus::Activate(BallsVec_t& balls, Paddle* paddle){
	if (isActivated)
		return;
	for (auto ball : balls) {
		ball->SetAngle(ball->GetAngle() / (rand() % 2 + 1));
	}
	isActivated = true;
}

SpeedDownBonus::SpeedDownBonus(cocos2d::Node* parent, Point position): Bonus(BONUS_TYPE_BALL_SPEED_DOWN, parent, position) {}

void SpeedDownBonus::Activate(BallsVec_t& balls, Paddle* paddle){
	if (isActivated)
		return;
	for (auto ball : balls)
		ball->ChangeVelocity(-VELOCITY_DELTA);
	isActivated = true;
}

ExtendPaddleBonus::ExtendPaddleBonus(cocos2d::Node* parent, Point position) : Bonus(BONUS_TYPE_RESIZE_PADDLE, parent, position) {}

void ExtendPaddleBonus::Activate(BallsVec_t& balls, Paddle* paddle){
	if (isActivated)
		return;
	auto paddleSprite = sprite->getParent()->getChildByName("Paddle");
	paddleSprite->setScaleX(paddleSprite->getScaleX() + 0.05);
	isActivated = true;
}