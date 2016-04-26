#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "MagicHero.h"
#include "HeroStatusBar.h"
#include "MagicMonster.h"

#define _MESSAGE_SYSTEM_ 0
#define _MESSAGE_HERO_LOSS_HP_ 1
#define _MESSAGE_MONSTER_LOSS_HP_ 2

class GameMainScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	static char* G2U(const char* gb2312);//中文UTF-8字符转换函数

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameMainScene);

	MagicHero *myMagicHero;

	void update(float delta);
	~GameMainScene();
private:

	//游戏地图文件
	cocos2d::CCTMXTiledMap *myTMXTiledMap;
	cocos2d::CCTMXLayer *barrierLayer;

	//按键响应函数
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);

	bool isHeroMoveAvailable();//判断英雄是否可以移动
	int dealObjects(cocos2d::CCTMXObjectGroup* objects, cocos2d::Vec2 position);
	void removeLabel(cocos2d::CCNode* sender, const char* name);//显示后移除label控件
	void showMessage(int type, cocos2d::String* message, bool isChinese);//显示消息,type对应消息类型
	cocos2d::Vec2 getDeltaPostion();
	bool dealInterAction(cocos2d::ValueMap vmap);

	int winHeight, winWidth;//游戏窗口大小
	int mapHeight, mapWidth;//游戏地图大小
	int moveCount;//移动计数，使英雄移动更加平滑
	int fightCount;//战斗计数，使战斗回合制进行
	bool heroFightTurn;//判断是否是英雄的回合

	const char* InfoName[3] = { "TIPS","DECHP", "DECHP" };

	cocos2d::TMXObjectGroup* objects;//当前地图的可互动对象及英雄集合
	cocos2d::ValueVector monsters;//怪物数据词典
	MagicMonster* currMonster;//当前战斗怪物
	HeroStatusBar* statusBar;
};

#endif