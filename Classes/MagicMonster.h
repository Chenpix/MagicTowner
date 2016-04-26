#ifndef __MAGIC_MONSTER__
#define __MAGIC_MONSTER__

#include "cocos2d.h"

class MagicMonster
{
public:
	MagicMonster(cocos2d::ValueMap monster);
	~MagicMonster();

	int getMonsterAttack();
	int getMonsterHP();
	int getMonsterDefend();
	cocos2d::String getMonsterName();

	int lessenHP(int attack);

private:
	int HP;
	int attack;
	int defend;
	cocos2d::String name;
};

#endif // !__MAGIC_MONSTER__
