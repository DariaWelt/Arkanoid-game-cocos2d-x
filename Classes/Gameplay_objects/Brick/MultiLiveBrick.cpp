# include "MultiLiveBrick.h"
#include "Constants.h"

USING_NS_CC;

MultiLiveBrick::MultiLiveBrick(int colorType, cocos2d::Node* parent, int healthPoints): Brick(colorType, parent), hp(healthPoints) {
	if (hp > 3 || hp <= 0) {
		hp = 3;
	}
	hpSprites = SpritesVec_t();
	for (int i = 0; i < hp; ++i) {
		hpSprites.push_back(Sprite::create(BRICK_HP_TEXTURE));
		sprite->addChild(hpSprites[i]);
		hpSprites[i]->setPosition(sprite->getContentSize().width * (float)(i + 1) * 0.25f, sprite->getContentSize().height * 0.5f);
	}
}


void MultiLiveBrick::HandleCollision(Ball* ball) {
	if (hp > 0) {
		--hp;
		hpSprites[hp]->removeFromParentAndCleanup(true);
		hpSprites.pop_back();
	}
}
Brick::BrickState MultiLiveBrick::GetState() const {
	if (hp <= 0) {
		return BrickState::BROKEN;
	}
	else {
		return BrickState::ALIVE;
	}
}