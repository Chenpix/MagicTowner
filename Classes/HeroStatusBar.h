#ifndef __HERO_STATUS_BAR__
#define __HERO_STATUS_BAR__

#include "cocos2d.h"

class HeroStatusBar : public cocos2d::CCNode {

public:
	bool init();

	void addIronKeysNum();	//��Կ������+1
	void addCopperKeysNum();//ͭԿ������+1
	void addGoldenKeysNum();//��Կ������+1

	int lessenHP(int attack);//��Ѫ��Ӧ����
	int getHeroAttack();

	HeroStatusBar();
	~HeroStatusBar();

private:
	int HP;				//Ӣ��Ѫ��
	int maxHP;			//Ӣ�����Ѫ��
	int EXP;			//Ӣ�۵�ǰӵ�о���ֵ
	int maxEXP;			// Ӣ�۵�ǰ�ȼ������ֵ
	int level;			//Ӣ�۵�ǰ�ȼ�
	int heroAttack;		//Ӣ�۹���
	int heroDefend;		//Ӣ�۷���
	int ironKeysNum;	//��Կ������
	int copperKeysNum;	//ͭԿ������
	int goldenKeysNum;	//��Կ������

	cocos2d::CCLabelAtlas* hpLabel;
	cocos2d::CCProgressTimer* hpProgress;
};

#endif // !__HERO_STATUS_BAR__