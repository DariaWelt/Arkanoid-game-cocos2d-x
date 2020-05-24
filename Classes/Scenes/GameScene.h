#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "Gameplay_objects/Paddle.h"
#include "Gameplay_objects/Ball.h"
#include "Gameplay_objects/Bonus.h"
#include "Gameplay_objects/Brick/Brick.h"
#include "Gameplay_objects/Brick/MultiLiveBrick.h"
#include "Gameplay_objects/Brick/SingleLiveBrick.h"
#include "Gameplay_objects/Brick/Unbreakable.h"
#include <utility>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using BricksField_t = std::vector<std::vector<Brick*>>;
using BallsVec_t = std::vector<Ball*>;
using BonusesVec_t = std::vector<Bonus*>;
using std::pair;


class GameScene : public cocos2d::Scene {
public:
  GameScene();

  static cocos2d::Scene* createScene();
  virtual bool init() override;
  virtual void update(float dt) override;
  void MenuCloseCallback(const cocos2d::Ref* pSender);
  CREATE_FUNC(GameScene);

private:
  void InitUpperBar();
  void InitGameField();
  void InitPaddle();
  void Initlistener();
  void InitBall();
  void InitBricks();
  void SpawnRandBricks(int type, int number);

  void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
  void OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

  void HandleCollisions();
  void PaddleCollisionCallback(Ball* ball);
  bool BallCollisionCallback(Ball* ball, const Rect& collidedRect, bool isPaddle);
  void BrickCollisionCallback(int i, int j, Ball* ball);
  Point GetFieldCoords(int i, int j) const;

  bool isWon();
  bool isFail();
  void Exit();

private:
  BallsVec_t balls;
  BricksField_t bricks;
  BonusesVec_t fallingBonuses;
  Paddle* paddle;
  Sprite* bottom;
  float scale;
};
