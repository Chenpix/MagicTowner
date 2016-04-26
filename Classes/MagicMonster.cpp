#include "MagicMonster.h"

MagicMonster::MagicMonster(cocos2d::ValueMap monster)
{
	HP = monster["hp"].asInt();
	attack = monster["attack"].asInt();
	defend = monster["defend"].asInt();
	name = monster["name"].asString();
}

MagicMonster::~MagicMonster()
{
}

int MagicMonster::getMonsterAttack()
{
	return attack;
}

int MagicMonster::getMonsterHP()
{
	return HP;
}

int MagicMonster::getMonsterDefend()
{
	return defend;
}

cocos2d::String MagicMonster::getMonsterName()
{
	return cocos2d::String();
}

int MagicMonster::lessenHP(int attack)
{
	if (HP <= attack - defend) {
		return -1;
	}
	if (attack > defend) {
		HP -= attack - defend;
	}
	return attack - defend;
}
