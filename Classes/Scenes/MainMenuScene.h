#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
/**
@brief    The start game screen with Play, Info and Exit buttons
*/
class MainMenuScene : public cocos2d::Scene {
  bool isInfoScreen;
  float scale;

  bool InitBackground();
  void InitMenu();

public:
  static cocos2d::Scene* createScene();
  /**
   @brief  Initialization of the main menu scene with background and main combonents (buttons, lables)
   */
  virtual bool init();

  void menuCloseCallback(cocos2d::Ref* pSender);
  CREATE_FUNC(MainMenuScene);
};