#include "HeroStatusBar.h"
#include "GameMainScene.h"
#include "MagicHero.h"

USING_NS_CC;

bool HeroStatusBar::init()
{
	hpProgress = CCProgressTimer::create(CCSprite::create("blod_fg.png"));
	hpProgress->setType(CCProgressTimerType::RADIAL);
	hpProgress->setScale(3 * _BLOCK_SIZE_ / hpProgress->getContentSize().width);
	hpProgress->setAnchorPoint(Vec2(0, 0));
	hpProgress->setPosition(20, 0);
	hpProgress->setPercentage(100);
	this->addChild(hpProgress, 3);

	auto hpBG = CCSprite::create("blood_bg.png");
	hpBG->setScale(3 * _BLOCK_SIZE_ / hpBG->getContentSize().width);
	hpBG->setAnchorPoint(Vec2(0, 0));
	hpBG->setPosition(20, 0);
	this->addChild(hpBG, 2);

	auto heroHead = CCSprite::create("/hero/headportrait.png");
	heroHead->setScale(3 * _BLOCK_SIZE_ / heroHead->getContentSize().width);
	heroHead->setAnchorPoint(Vec2(0, 0));
	heroHead->setPosition(20, 0);
	this->addChild(heroHead, 1);

	auto string = GameMainScene::G2U("ÑªÁ¿:");
	auto heroHP = CCLabelTTF::create(string, "Á¥Êé", 30);
	heroHP->setAnchorPoint(Vec2(0, 0));
	heroHP->setPosition(5 * _BLOCK_SIZE_, _BLOCK_SIZE_*1.5);
	heroHP->setColor(Color3B(255, 0, 0));
	this->addChild(heroHP, 3);

	hpLabel = CCLabelAtlas::create("1000/1000", "number.png", 12, 32, 46);
	hpLabel->setPosition(ccp(100, 100));
	hpLabel->setAnchorPoint(Vec2(0, 0));
	hpLabel->setPosition(8 * _BLOCK_SIZE_, _BLOCK_SIZE_*1.5);
	hpLabel->setScale(1.5);
	this->addChild(hpLabel, 3, "HP");

	delete[] string;
	return true;
}

void HeroStatusBar::addIronKeysNum()
{
}

void HeroStatusBar::addCopperKeysNum()
{
}

void HeroStatusBar::addGoldenKeysNum()
{
}

int HeroStatusBar::lessenHP(int attack)
{
	if (HP <= attack - heroDefend) {
		return -1;
	}
	if (attack > heroDefend) {
		HP -= attack - heroDefend;
		auto s = String::createWithFormat("%d/%d", HP, maxHP);
		hpLabel->setString(s->getCString());
		hpProgress->setPercentage(HP * 100 / maxHP);
		return attack - heroDefend;
	}
	return 0;
}

int HeroStatusBar::getHeroAttack()
{
	return heroAttack;
}

HeroStatusBar::HeroStatusBar()
{
	HP = 1000;
	maxHP = HP;
	EXP = 0;
	level = 1;
	maxEXP = level*level * 50;
	heroAttack = 100;		//Ó¢ÐÛ¹¥»÷
	heroDefend = 20;		//Ó¢ÐÛ·ÀÓù
	ironKeysNum = 1;	//ÌúÔ¿³×ÊýÁ¿
	copperKeysNum = 1;	//Í­Ô¿³×ÊýÁ¿
	goldenKeysNum = 1;	//½ðÔ¿³×ÊýÁ¿
	init();
}

HeroStatusBar::~HeroStatusBar()
{
}
