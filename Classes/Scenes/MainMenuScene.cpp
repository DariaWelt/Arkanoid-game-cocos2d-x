#include "MainMenuScene.h"
#include "Constants.h"
#include "GameScene.h"

Scene* MainMenuScene::createScene() {
  return MainMenuScene::create();
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SplashSceneScene.cpp\n");
}


// on "init" you need to initialize your instance
bool MainMenuScene::init() {
  // super init first
  isInfoScreen = false;
  if (!Scene::init()) {
    return false;
  }
  if (!InitBackground())
    return false;
  InitMenu();
  return true;
}


bool MainMenuScene::InitBackground() {

  auto director = Director::getInstance();
  auto visibleSize = director->getVisibleSize();
  Vec2 origin = director->getVisibleOrigin();

  // add "MainMenuScene" background and title
  auto background = Sprite::create(START_MENU_BACKGROUND);
  auto title = Sprite::create(START_MENU_TITLE_GIF);
  if (background == nullptr || title == nullptr) {
    problemLoading("main menu components");
    return false;
  }

  // position the sprite on the center of the screen
  scale = visibleSize.width / background->getContentSize().width;
  background->setScale(scale);
  title->setScale(scale * 1.5f);
  background->setPosition(Vec2(visibleSize.width / 2.0f + origin.x, visibleSize.height / 2.0f + origin.y));
  title->setPosition(Vec2(visibleSize.width / 2.0f + origin.x, visibleSize.height * 0.83f + origin.y));

  // add the sprite as a child to this layer
  this->addChild(background);
  this->addChild(title);
  return true;
}


void MainMenuScene::InitMenu() {
  auto director = Director::getInstance();
  auto visibleSize = director->getVisibleSize();
  Vec2 origin = director->getVisibleOrigin();

  // add a menu items: play
  auto playItem = MenuItemImage::create(START_MENU_PLAY_BUTTON_REST, START_MENU_PLAY_BUTTON_PRESSED, [&](Ref* sender) {
    if (isInfoScreen) {
      return;
    }
    auto scene = GameScene::createScene();
    // transition stage between scenes
    auto transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene, Color3B::BLACK);
    Director::getInstance()->replaceScene(transition);
    });
  playItem->setScale(scale);


  auto menu = Menu::create(playItem, nullptr);
  menu->setPosition(visibleSize.width / 2.0f + origin.x, visibleSize.height * 0.5f + origin.y);
  this->addChild(menu);
}


void MainMenuScene::menuCloseCallback(Ref* pSender) {
  if (!isInfoScreen) {
    Director::getInstance()->end();
  }
}
