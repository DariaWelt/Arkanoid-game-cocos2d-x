#include "GameScene.h"
#include "Constants.h"
#include "MainMenuScene.h"
#include <random>
#include <ctime>

GameScene::GameScene(): scale(1), paddle(nullptr) {
  balls = BallsVec_t();
}

Scene* GameScene::createScene() {
  return GameScene::create();
}

bool GameScene::init() {
  if (!Scene::init()) {
     return false;
  }

  auto director = Director::getInstance();
  auto visibleSize = director->getVisibleSize();
  Vec2 origin = director->getVisibleOrigin();
  
  // add "GameScene" background 
  auto background = Sprite::create(GAME_BACKGROUND);
  background->setName("Game background");
  scale = visibleSize.width / background->getContentSize().width;
  background->setScale(scale);
  background->setPosition(Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.5f + origin.y));
  this->addChild(background);

  InitUpperBar();
  InitGameField();
  InitPaddle();
  InitBall();
  Initlistener();
  InitBricks();
  this->scheduleUpdate();
  return true;
}

void GameScene::InitUpperBar() {
  auto visibleSize = Director::getInstance()->getVisibleSize();

  auto upperBar = Sprite::create(GAME_UPPER_BAR_BACKGROUND);
  upperBar->setName("Upper bar");
  upperBar->setScale(scale);
  upperBar->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.97f));
  this->addChild(upperBar);

 // home button
  auto toHomeItem = MenuItemImage::create(BACK_BUTTON_REST, BACK_BUTTON_PRESSED, [&](Ref* sender) {
    auto scene = MainMenuScene::createScene();
    // transition stage between scenes
    auto transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene, Color3B::BLACK);
    Director::getInstance()->replaceScene(transition);
    });
  auto menu = Menu::create(toHomeItem, nullptr);
  menu->setPosition(Vec2(upperBar->getContentSize().width * 0.05f, upperBar->getContentSize().height * 0.4f));
  upperBar->addChild(menu);

}

void GameScene::InitPaddle() {
  auto parent = this->getChildByName("Game field");
  paddle = new Paddle(parent);

  bottom = Sprite::create(GAME_BOTTOM);
  bottom->setName("Bottom");
  parent->addChild(bottom);
  bottom->setAnchorPoint(Vec2(0, 0));
  bottom->setNormalizedPosition(Vec2(0, 0));
  bottom->setOpacity(0);
}

void GameScene::Initlistener() {
  auto listener = EventListenerKeyboard::create();
  listener->setEnabled(true);
  listener->onKeyPressed = CC_CALLBACK_2(GameScene::OnKeyPressed, this);
  listener->onKeyReleased = CC_CALLBACK_2(GameScene::OnKeyReleased, this);
  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this->getChildByName("Game field"));
}

void GameScene::InitGameField() {
  srand((unsigned int)time(nullptr));
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto barHeight = this->getChildByName("Upper bar")->getContentSize().height * this->getChildByName("Upper bar")->getScale();
  auto gameField = Node::create();
  gameField->setScale(scale);
  gameField->setName("Game field");
  gameField->setAnchorPoint(Vec2(0.0f, 0.0f));
  gameField->setContentSize(Size(visibleSize.width / scale, (visibleSize.height - barHeight) / scale));
  this->addChild(gameField);
}

void GameScene::InitBricks() {

  auto gameField = this->getChildByName("Game field");
  bricks = BricksField_t(GAME_BRICKS_LINES, std::vector<Brick*>(GAME_BRICKS_COLS, nullptr));

  int unbreakableNumber = rand() % (int)(GAME_BRICKS_LINES * GAME_BRICKS_COLS * GAME_BLOCKED_PROBABILITY);
  int bonusNumber = rand() % (int)(GAME_BRICKS_LINES * GAME_BRICKS_COLS * GAME_BONUS_PROBABILITY);
  int speedUpNumber = rand() % (int)(GAME_BRICKS_LINES * GAME_BRICKS_COLS * GAME_SPEEDUP_PROBABILITY);

  SpawnRandBricks(BRICK_TYPE_UNBREAKABLE, unbreakableNumber);
  SpawnRandBricks(BRICK_TYPE_SPEEDUP, speedUpNumber);
  SpawnRandBricks(-1, bonusNumber);

  for (int i = 0; i < GAME_BRICKS_LINES; ++i) {
    for (int j = 0; j < GAME_BRICKS_COLS; ++j) {
      if (bricks[i][j] == nullptr) {
        bricks[i][j] = (Brick*)(new MultiLiveBrick(rand() % 4 + BRICK_TYPE_SIMPLE, gameField, rand() % 3 + 1));
        bricks[i][j]->SetPosition(GetFieldCoords(i, j));
      }
      bricks[i][j]->SetScale((gameField->getContentSize().width / GAME_BRICKS_COLS / BRICK_WIDTH));
    }
  }
}

void GameScene::SpawnRandBricks(int type, int number) {
  auto gameField = this->getChildByName("Game field");
  for (int k = 0; k < number; ++k) {
    while (true) {
      int i = rand() % GAME_BRICKS_LINES, j = rand() % GAME_BRICKS_COLS;
      if (bricks[i][j] == nullptr) {
        switch (type) {
        case BRICK_TYPE_UNBREAKABLE:
          bricks[i][j] = (Brick*)(new Unbreakable(gameField));
          break;
        case BRICK_TYPE_SPEEDUP:
          bricks[i][j] = (Brick*)(new SpeedUpBrick(gameField));
          break;
        case -1:
          bricks[i][j] = (Brick*)(new BonusBrick(rand() % 4 + BRICK_TYPE_SIMPLE, gameField, fallingBonuses));
          break;
        }
        bricks[i][j]->SetPosition(GetFieldCoords(i, j));
        break;
      }
    }
  }
}

void GameScene::InitBall() {
  auto parent = this->getChildByName("Game field");
  Ball* ball = new Ball(parent);
  balls.push_back(ball);
}
