#pragma once

#define FONT_PATH "fonts/AA-neon.ttf"
#define SCENE_TRANSITION_TIME 0.3f // sec
#define BACK_BUTTON_REST "res/back_to_menu.png"
#define BACK_BUTTON_PRESSED "res/back_to_menu.png"

// settings scene
#define SETTINGS_SOUND_ON_BUTTON_REST ""
#define SETTINGS_SOUND_OFF_BUTTON_REST ""
#define SETTINGS_SOUND_ON_BUTTON_PRESSED ""
#define SETTINGS_SOUND_OFF_BUTTON_PRESSED ""
#define SETTINGS_INFO_BUTTON_REST ""
#define SETTINGS_INFO_BUTTON_PRESSED ""

#define SETTINGS_INFO_BACKGROUND ""
#define SETTINGS_INFO_DESIGN_PROVIDER ""

// splash scene
#define SPLASH_BACKGROUND "res/splash_scene_background.png"
#define SPLASH_SHOW_TIME 2.0f // sec

// start menu scene
#define START_MENU_BACKGROUND "res/background.png"
#define START_MENU_PLAY_BUTTON_REST "res/play_button.png"
#define START_MENU_PLAY_BUTTON_PRESSED "res/play_button.png"
#define START_MENU_TITLE_GIF "res/game_title.png"

// game scene
#define GAME_BACKGROUND "res/background.png"
#define GAME_UPPER_BAR_BACKGROUND "res/top_bar.png"
#define GAME_BOTTOM "res/bottom.png"
#define GAME_HEART_IMAGE "res/heart.png"
#define GAME_LIVES_NUMBER 3 // max - 5
#define GAME_BRICKS_LINES 5
#define GAME_BRICKS_COLS 7
#define GAME_FIELD_POS_X 0.0f // pixels
#define GAME_FIELD_POS_Y 0.0f // pixels
#define GAME_FIELD_SIZE_W 1024.0f // pixels
#define GAME_FIELD_SIZE_H 1177.0f // pixels

#define GAME_BLOCKED_PROBABILITY 0.2f
#define GAME_BONUS_PROBABILITY 0.2f
#define GAME_SPEEDUP_PROBABILITY 0.1f

#define BONUS_VELOCITY 500.0f // pixel/ sec
#define BALL_VELOCITY 900.0f // pixel/ sec
#define VELOCITY_DELTA 100.0f // pixel/ sec

// objects
#define BALL_TEXTURE "res/ball.png"
#define PADDLE_TEXTURE "res/paddle.png"
#define PADDLE_VELOCITY 10.0f // pixels
#define BRICK_ATLAS "res/briks_no_glow.png"
#define BRICK_WIDTH 157.0f
#define BRICK_HEIGHT 63.0f
#define BRICK_HP_TEXTURE "res/hp.png"
#define BRICK_BOUNS_TEXTURE "res/bonus_brick.png"
#define BRICK_VELOCITY 300 // pixel/sec
#define BONUS_ATLAS "res/bonuses.png"
#define BONUS_NUMBER 6
#define BONUS_SIZE 302 // pixels

#define GAME_WON_BACKGROUND "res/background_won.png"
#define GAME_WON_TITLE_GIF "res/congratulations_title.png"

enum GameState {
	GAME_STATE_PLAYING = 1,
	GAME_STATE_WON,
};

enum BrickType {
	BRICK_TYPE_UNBREAKABLE,
	BRICK_TYPE_SPEEDUP,
	BRICK_TYPE_SIMPLE
};

enum BonusType {
	BONUS_TYPE_RESIZE_PADDLE,
	BONUS_TYPE_NEW_BALL,
	BONUS_TYPE_RAND_TRAGECTORY,
	BONUS_TYPE_SHILD,
	BONUS_TYPE_MAGNET,
	BONUS_TYPE_BALL_SPEED_DOWN
};