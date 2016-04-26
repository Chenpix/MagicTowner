#ifndef __HERO_STATUS_BAR__
#define __HERO_STATUS_BAR__

#include "cocos2d.h"

class HeroStatusBar : public cocos2d::CCNode {

public:
	bool init();

	void addIronKeysNum();	//铁钥匙数量+1
	void addCopperKeysNum();//铜钥匙数量+1
	void addGoldenKeysNum();//金钥匙数量+1

	int lessenHP(int attack);//扣血反应函数
	int getHeroAttack();

	HeroStatusBar();
	~HeroStatusBar();

private:
	int HP;				//英雄血量
	int maxHP;			//英雄最大血量
	int EXP;			//英雄当前拥有经验值
	int maxEXP;			// 英雄当前等级最大经验值
	int level;			//英雄当前等级
	int heroAttack;		//英雄攻击
	int heroDefend;		//英雄防御
	int ironKeysNum;	//铁钥匙数量
	int copperKeysNum;	//铜钥匙数量
	int goldenKeysNum;	//金钥匙数量

	cocos2d::CCLabelAtlas* hpLabel;
	cocos2d::CCProgressTimer* hpProgress;
};

#endif // !__HERO_STATUS_BAR__