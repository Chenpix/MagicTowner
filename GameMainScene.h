#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "MagicHero.h"

class GameMainScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameMainScene);

	MagicHero *myMagicHero;

	void update(float delta);

private:

	//游戏地图文件
	cocos2d::CCTMXTiledMap *myTMXTiledMap;
	cocos2d::CCTMXLayer *barrierLayer;

	//按键响应函数
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);

	bool isHeroMoveAvailable();//判断英雄是否可以移动
	char* G2U(const char* gb2312);//中文UTF-8字符转换函数
	bool dealObjects(cocos2d::CCTMXObjectGroup* objects, cocos2d::Vec2 position);
	void removeLabel();//显示后移除label控件

	int winHeight, winWidth;//游戏窗口大小
	int mapHeight, mapWidth;//游戏地图大小
	int moveCount;//移动计数，使英雄移动更加平滑

	cocos2d::TMXObjectGroup* objects;
};

#endif