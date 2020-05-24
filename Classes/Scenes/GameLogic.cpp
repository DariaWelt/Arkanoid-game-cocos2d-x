#include "GameScene.h"
#include "Constants.h"
#include <random>
#include <ctime>
#include "MainMenuScene.h"

using std::_Pi;

void GameScene::MenuCloseCallback(const Ref* pSender) {
  Director::getInstance()->end();
}

void GameScene::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
  switch (keyCode) {
  case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
  case EventKeyboard::KeyCode::KEY_A:
    this->paddle->SetMovement(-1);
    break;

  case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
  case EventKeyboard::KeyCode::KEY_D:
    this->paddle->SetMovement(1);
    break;
  }
}

void GameScene::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
  switch (keyCode) {

  case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
  case EventKeyboard::KeyCode::KEY_A:
    if (this->paddle->GetMovement() == -1)
      this->paddle->SetMovement(0);
    break;

  case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
  case EventKeyboard::KeyCode::KEY_D:
    if (this->paddle->GetMovement() == 1)
      this->paddle->SetMovement(0);
    break;

  case EventKeyboard::KeyCode::KEY_SPACE:
    for (auto ball : balls) {
      if (ball->GetState() == Ball::BallState::CAPTURED)
        ball->SetState(Ball::BallState::FREE);
    }
    paddle->SetState(Paddle::PaddleState::SIMPLE);
    break;
  }
}

void GameScene::update(float dt) {
  paddle->UpdateState();
  for (auto ball : balls)
    ball->UpdatePosition(dt);
  HandleCollisions();

  if (isWon() || isFail()) {
    auto scene = MainMenuScene::create();
    auto transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene, Color3B::BLACK);
    Director::getInstance()->replaceScene(transition);
  }
  
  int size = fallingBonuses.size();
  for (int i = size - 1; i >= 0; --i) {
    if (fallingBonuses[i]->MovingIsDone()) {
      delete(fallingBonuses[i]);
      fallingBonuses.erase(fallingBonuses.begin() + i);
    }
  }

  size = balls.size();
  for (int i = size - 1; i >= 0; --i) {
    if (balls[i] == nullptr) {
      balls.erase(balls.begin() + i);
    }
  }
}

void GameScene::HandleCollisions() {

  auto origin = Director::getInstance()->getVisibleOrigin();
  auto gameFieldSize = this->getChildByName("Game field")->getContentSize();

  // handle all balls
  for (auto& ball : balls) {
    if (ball->IsGrabbled())
      continue;
    const Rect ballRect = ball->GetRect();
    float paddleKoeff = 0.75f;

    // intersection with walls
    if (ballRect.getMinY() < origin.y || ballRect.getMaxY() > origin.y + gameFieldSize.height) {
      ball->SetAngle(2 * _Pi - ball->GetAngle());
      if (ballRect.getMinY() < origin.y) {
        delete(ball);
        ball = nullptr;
        continue;
      }
      else {
        ball->ChangePosition(0, origin.y + gameFieldSize.height - ballRect.getMaxY());
      }
    }

    else if (ballRect.getMinX() < origin.x || ballRect.getMaxX() > origin.x + gameFieldSize.width) {
      ball->SetAngle(_Pi - ball->GetAngle());
      if (ballRect.getMinX() < origin.x) {
        ball->ChangePosition(origin.x - ballRect.getMinX(), 0);
      }
      else {
        ball->ChangePosition(origin.x + gameFieldSize.width - ballRect.getMaxX(), 0);
      }
    }

    // intersection with paddle
    else if (ballRect.intersectsRect(paddle->GetRect()) && BallCollisionCallback(ball, paddle->GetRect(), true)) {
      PaddleCollisionCallback(ball);
    }


    else if (ballRect.intersectsRect(bottom->getBoundingBox()) && bottom->getOpacity() == 100 && BallCollisionCallback(ball, bottom->getBoundingBox(), false)) {
      bottom->setOpacity(0);
    }
    
    else {
      // intersection with bricks
      for (int i = 0; i < GAME_BRICKS_LINES; ++i) {
        for (int j = 0; j < GAME_BRICKS_COLS; ++j) {
          if (bricks[i][j] != nullptr && ballRect.intersectsRect(bricks[i][j]->GetRect()) && BallCollisionCallback(ball, bricks[i][j]->GetRect(), false)) {
            BrickCollisionCallback(i, j, ball);
          }
        }
      }

      // intersection with balls
      for (auto ball2 : balls) {
        if (ball2 != nullptr && ball != ball2 && ballRect.intersectsRect(ball2->GetRect()))
          BallCollisionCallback(ball, ball2->GetRect(), false);
      }
    }
  }

  // handle bonuses
  for (auto bonus : fallingBonuses) {
    auto bonusRect = bonus->GetRect();
    if (bonusRect.intersectsRect(paddle->GetRect()) &&  bonusRect.getMinY() <= paddle->GetRect().getMaxY()) {
      bonus->Activate(balls, paddle);
    }
  }
}

bool GameScene::BallCollisionCallback(Ball* ball, const Rect& collidedRect, bool isPaddle) {
  auto ballRect = ball->GetRect();

  // ball trejectory ballPosY = ballPosX * tg(ballAngle) + b 
  float k = std::tan(ball->GetAngle());
  float b = ball->GetPosition().y - k * ball->GetPosition().x;

  Point crossSide1 = Vec2((collidedRect.getMaxY() - b) / k, collidedRect.getMaxY());
  Point crossSide2 = Vec2(collidedRect.getMaxX(), k * collidedRect.getMaxX() + b);
  Point crossSide3 = Vec2((collidedRect.getMinY() - b) / k, collidedRect.getMinY());
  Point crossSide4 = Vec2(collidedRect.getMinX(), k * collidedRect.getMinX() + b);

  bool isVertical;


  // horizontal line collision
  if (crossSide1.x <= collidedRect.getMaxX() && crossSide1.x >= collidedRect.getMinX()
    && crossSide3.x <= collidedRect.getMaxX() && crossSide3.x >= collidedRect.getMinX())
    isVertical = false;


  // vertical line collision
  else if (crossSide2.y <= collidedRect.getMaxY() && crossSide2.y >= collidedRect.getMinY()
    && crossSide4.y <= collidedRect.getMaxY() && crossSide4.y >= collidedRect.getMinY())
    isVertical = true;


  // if handle first side
  else if (crossSide1.x <= collidedRect.getMaxX() && crossSide1.x >= collidedRect.getMinX()) {
    if (ball->GetAngle() > _Pi)
      isVertical = false;
    else
      isVertical = true;
  }
  // else second with third or third with forth
  else if (crossSide3.x <= collidedRect.getMaxX() && crossSide3.x >= collidedRect.getMinX()) {
    if (ball->GetAngle() > _Pi)
      isVertical = true;
    else
      isVertical = false;
  }

  else
    return false;

  float paddleKoeff = ballRect.getMidX() / collidedRect.getMidX();

  if (isVertical) {
    ball->SetAngle(_Pi - ball->GetAngle());
    if (ball->GetAngle() > _Pi * 0.5 && ball->GetAngle() < _Pi * 1.5)
      ball->ChangePosition(collidedRect.getMinX() - ballRect.getMaxX() - 1, 0);
    else
      ball->ChangePosition(collidedRect.getMaxX() - ballRect.getMinX() + 1, 0);

  }

  else {
    if (isPaddle)
      ball->SetAngle(_Pi * 0.5 + (_Pi * 1.5 - ball->GetAngle()) * paddleKoeff);
    else
      ball->SetAngle(2 * _Pi - ball->GetAngle());
    if (ball->GetAngle() > _Pi)
      ball->ChangePosition(0, collidedRect.getMinY() - ballRect.getMaxY() - 1);
    else
      ball->ChangePosition(0, collidedRect.getMaxY() - ballRect.getMinY() + 1);
  }
  return true;
}

void GameScene::PaddleCollisionCallback(Ball* ball) {
  if (paddle->GetState() == Paddle::PaddleState::MAGNETED) {
    ball->SetState(Ball::BallState::CAPTURED);
  }
}

void GameScene::BrickCollisionCallback(int i, int j, Ball* ball) {
  bricks[i][j]->HandleCollision(ball);
  if (bricks[i][j]->GetState() == Brick::BrickState::BROKEN) {
    delete(bricks[i][j]);
    bricks[i][j] = nullptr;
  }
}


Point GameScene::GetFieldCoords(int i, int j) const {
  if (i < 0 || i > GAME_BRICKS_LINES || j < 0 || j  > GAME_BRICKS_COLS) {
    return Vec2(0, 0);
  }
  else {
    auto gameFieldRect = this->getChildByName("Game field")->getBoundingBox();
    float brickWidth = (gameFieldRect.size.width / GAME_BRICKS_COLS);
    float brickHeight = (BRICK_HEIGHT) / (BRICK_WIDTH) * brickWidth;
    return Vec2(gameFieldRect.getMinX() + brickWidth * ((float)j + 0.5f),
                gameFieldRect.getMaxY() - brickHeight * ((float)i + 0.5f)) / scale;
  }
}

bool GameScene::isWon() {
  for (auto line : bricks) {
    for (auto brick : line) {
      if (brick != nullptr && brick->GetType() != BRICK_TYPE_UNBREAKABLE)
        return false;
    }
  }
  return true;
}

bool GameScene::isFail() {
  if (balls.size() == 0)
    return true;
  else
    return false;
}

void GameScene::Exit() {
  using namespace std;

  if (paddle != nullptr) {
    delete(paddle);
    paddle = nullptr;
  }
  if (bottom != nullptr) {
    bottom->removeFromParentAndCleanup(true);
    bottom = nullptr;
  }

  for_each(balls.begin(), balls.end(), default_delete<Ball>());
  for_each(fallingBonuses.begin(), fallingBonuses.end(), default_delete<Bonus>());
  for (auto& line : bricks) {
    for_each(line.begin(), line.end(), default_delete<Brick>());
  }

}