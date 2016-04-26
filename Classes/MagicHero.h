#ifndef __HERO__H_
#define __HERO__H_

#include "cocos2d.h"

#define _BLOCK_SIZE_ 32

class MagicHero : public cocos2d::CCSprite
{
public:
	~MagicHero();

	static MagicHero* getHeroInstance();

	const static int UP = 0;
	const static int DOWN = 1;
	const static int LEFT = 2;
	const static int RIGHT = 3;

	//移动一格，返回一个移动位移偏移量
	cocos2d::Vec2 moveHeroStep();

	//设置英雄方向
	void setHeroDirect(int dir);
	int getHeroDirect();

	//英雄移动相关操作
	void incIsMove();
	void decIsMove();
	void setIsMoveToZero();
	bool isHeroMove();

	//获取英雄地图坐标
	cocos2d::Point getHeroMapPosition();

	//英雄移动动画
	void idleHero();
	void runAnimation();
	void moveHeroToOneDirection();
	void stopHero();
	
	//英雄战斗相关
	void setFightStatus(bool isFighting);
	bool isHeroFighting();

private:
	MagicHero();
	int direct;//英雄当前面朝方向
	int pRoom;//所在房间
	int isMove;//英雄是否在移动
	bool isFighting;//英雄是否在战斗
	//Vector<int> bag;//英雄人物背包

	//英雄单例
	static MagicHero* heroInstance;

	cocos2d::Sprite *heroSprite;//英雄精灵

	//初始化英雄animation
	void initSpriteAndAnimation();

	//英雄动作
	cocos2d::Action *moveAction;

	char* idel[4];

	class Garbo
	{
	public:
		Garbo();
		~Garbo() {
			if (heroInstance != NULL)
			{
				delete MagicHero::heroInstance;
			}
		}

	};

	//垃圾回收器——静态变量会被回收
	static Garbo garbo;
};

#endif // !__HERO__H_