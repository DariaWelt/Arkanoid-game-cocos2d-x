#include "SingleLiveBrick.h"
#include "Constants.h"
#include <random>

USING_NS_CC;

SpeedUpBrick::SpeedUpBrick(cocos2d::Node* parent): Brick(BRICK_TYPE_SPEEDUP, parent), state(BrickState::ALIVE) {}
void SpeedUpBrick::HandleCollision(Ball* ball) {
	state = BrickState::BROKEN;
	ball->ChangeVelocity(VELOCITY_DELTA);
}
Brick::BrickState SpeedUpBrick::GetState() const {
	return state;
}

BonusBrick::BonusBrick(int brickColor, cocos2d::Node* parent, BonusesVec_t& gameBonuses): Brick(brickColor, parent), state(BrickState::ALIVE) {
	bonusIcon = Sprite::create(BRICK_BOUNS_TEXTURE);
	sprite->addChild(bonusIcon);
	bonusIcon->setNormalizedPosition(Vec2(0.5f, 0.5f));
	bonuses = &gameBonuses;
}
void BonusBrick::SpawnBonus() {
	int bonusType = rand() % BONUS_NUMBER;
	Bonus* bonus;
	Point position = Vec2(sprite->getBoundingBox().getMidX(), sprite->getBoundingBox().getMinY());
	switch (bonusType) {
	case BONUS_TYPE_RESIZE_PADDLE:
		bonus = (Bonus*) new ExtendPaddleBonus(sprite->getParent(), position);
		break;
	case BONUS_TYPE_NEW_BALL:
		bonus = (Bonus*) new NewBallBonus(sprite->getParent(), position);
		break;
	case BONUS_TYPE_RAND_TRAGECTORY:
		bonus = (Bonus*) new RandTrajectoryBonus(sprite->getParent(), position);
		break;
	case BONUS_TYPE_SHILD:
		bonus = (Bonus*) new ShildBonus(sprite->getParent(), position);
		break;
	case BONUS_TYPE_MAGNET:
		bonus = (Bonus*) new MagnetBonus(sprite->getParent(), position);
		break;
	case BONUS_TYPE_BALL_SPEED_DOWN:
		bonus = (Bonus*) new SpeedDownBonus(sprite->getParent(), position);
		break;
	}

	bonuses->push_back(bonus);
}
void BonusBrick::HandleCollision(Ball* ball) {
	state = BrickState::BROKEN;
	BonusBrick::SpawnBonus();
}
Brick::BrickState BonusBrick::GetState() const {
	return state;
}

