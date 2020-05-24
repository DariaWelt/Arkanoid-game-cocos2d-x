#include "Brick.h"
#include "Constants.h"

USING_NS_CC;

Brick::Brick(int brickType, cocos2d::Node* parent): typeID(brickType), sprite(nullptr)  {
	LoadIcon();
	parent->addChild(sprite);
}
Brick::~Brick() {
	if (sprite != nullptr) {
		sprite->removeFromParentAndCleanup(true);
		sprite = nullptr;
	}
}
void Brick::LoadIcon() {
	if (sprite != nullptr) {
		sprite->removeFromParentAndCleanup(true);
		sprite = nullptr;
	}
	PolygonInfo pinfo;
	switch (typeID) {
	case BRICK_TYPE_UNBREAKABLE:
		pinfo = AutoPolygon::generatePolygon(BRICK_ATLAS, Rect(BRICK_WIDTH * 1.0f, BRICK_HEIGHT * 1.0f, BRICK_WIDTH, BRICK_HEIGHT));
		break;
	case BRICK_TYPE_SPEEDUP:
		pinfo = AutoPolygon::generatePolygon(BRICK_ATLAS, Rect(BRICK_WIDTH * 1.0f, BRICK_HEIGHT * 2.0f, BRICK_WIDTH, BRICK_HEIGHT));
		break;
	case BRICK_TYPE_SIMPLE:
		pinfo = AutoPolygon::generatePolygon(BRICK_ATLAS, Rect(BRICK_WIDTH * 1.0f, BRICK_HEIGHT * 0, BRICK_WIDTH, BRICK_HEIGHT));
		break;
	case BRICK_TYPE_SIMPLE + 1:
		pinfo = AutoPolygon::generatePolygon(BRICK_ATLAS, Rect(BRICK_WIDTH * 0, BRICK_HEIGHT * 0, BRICK_WIDTH, BRICK_HEIGHT));
		break;
	case BRICK_TYPE_SIMPLE + 2:
		pinfo = AutoPolygon::generatePolygon(BRICK_ATLAS, Rect(BRICK_WIDTH * 0, BRICK_HEIGHT * 1.0f, BRICK_WIDTH, BRICK_HEIGHT));
		break;
	case BRICK_TYPE_SIMPLE + 3:
		pinfo = AutoPolygon::generatePolygon(BRICK_ATLAS, Rect(BRICK_WIDTH * 0, BRICK_HEIGHT * 2.0f, BRICK_WIDTH, BRICK_HEIGHT));
		break;
	}
	sprite = Sprite::create(pinfo);
}

Point Brick::GetPosition() const {
	return sprite->getPosition();
}

Rect Brick::GetRect() const {
	return sprite->getBoundingBox();
}

void Brick::SetPosition(cocos2d::Point position) {
	sprite->setPosition(position);
}

void Brick::SetScale(float scale) {
	sprite->setScale(scale);
}

int Brick::GetType() const {
	return typeID;
}