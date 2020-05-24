#include "Unbreakable.h"
#include "Constants.h"

USING_NS_CC;

Unbreakable::Unbreakable(cocos2d::Node* parent): Brick(BRICK_TYPE_UNBREAKABLE, parent) {}
void Unbreakable::HandleCollision(Ball* ball) {}
Brick::BrickState Unbreakable::GetState() const {
	return BrickState::ALIVE;
}