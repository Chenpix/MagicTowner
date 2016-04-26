#include "MagicHero.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;


void MagicHero::setFightStatus(bool isFighting)
{
	this->isFighting = isFighting;
	if (isFighting == false) {
		idleHero();
	}
	else {
		runAnimation();
	}
}

bool MagicHero::isHeroFighting()
{
	return isFighting;
}

MagicHero::MagicHero()
{
	this->direct = MagicHero::DOWN;//英雄当前面朝方向
	this->pRoom = 1;//所在房间
	this->isMove = 0;
	this->isFighting = false;

	CCSprite::init();
	
	initSpriteAndAnimation();
}

void MagicHero::idleHero()
{
	this->removeChild(heroSprite, true);
	char path[100] = {};
	sprintf_s(path, "%s1.png", idel[direct]);
	auto s = CCSprite::create(path);
	s->setAnchorPoint(Vec2(0.3, 0));
	this->addChild(s);
	heroSprite = s;
}

MagicHero::~MagicHero()
{
	if (heroSprite != NULL)
	{
		heroSprite->release();
		heroSprite = NULL;
	}
	if (moveAction != NULL)
	{
		moveAction->release();
		moveAction = NULL;
	}
}

MagicHero* MagicHero::heroInstance = NULL;

MagicHero * MagicHero::getHeroInstance()
{
	if (MagicHero::heroInstance == NULL)
	{
		MagicHero::heroInstance = new MagicHero();
	}
	return MagicHero::heroInstance;
}

Vec2 MagicHero::moveHeroStep()
{
	Vec2 v(0,0);
	switch (direct)
	{
	case MagicHero::UP:
		setPositionY(getPosition().y + _BLOCK_SIZE_);
		//heroSprite->setPositionY(heroSprite->getPosition().y + _BLOCK_SIZE_);
		v.y = _BLOCK_SIZE_;
		break;
	case MagicHero::DOWN:
		setPositionY(getPosition().y - _BLOCK_SIZE_);
		//heroSprite->setPositionY(heroSprite->getPosition().y - _BLOCK_SIZE_);
		v.y = -_BLOCK_SIZE_;
		break;
	case MagicHero::RIGHT:
		v.x = _BLOCK_SIZE_;
		setPositionX(getPosition().x + _BLOCK_SIZE_);
		//heroSprite->setPositionX(heroSprite->getPosition().x + _BLOCK_SIZE_);
		break;
	case MagicHero::LEFT:
		v.x = -_BLOCK_SIZE_;
		setPositionX(getPosition().x - _BLOCK_SIZE_);
		//heroSprite->setPositionX(heroSprite->getPosition().x - _BLOCK_SIZE_);
		break;
	default:
		break;
	}
	return v;
}
void MagicHero::initSpriteAndAnimation()
{

	idel[0] = "hero/u";
	idel[1] = "hero/d";
	idel[2] = "hero/l";
	idel[3] = "hero/r";
	idleHero();

	this->moveAction = NULL;
}

void MagicHero::setHeroDirect(int dir) 
{
	this->direct = dir;
}

void MagicHero::runAnimation()
{
	Vector<SpriteFrame*> allFrames;
	char path[100] = {};
	for (int i = 1; i < 4; i++) {
		sprintf_s(path, "%s%d.png", idel[direct], i);
		SpriteFrame *sf = SpriteFrame::create(path, Rect(0, 0, 72, 55));
		allFrames.pushBack(sf);
	}

	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.15);
	moveAction = heroSprite->runAction(RepeatForever::create(Animate::create(ani)));
}

bool MagicHero::isHeroMove()
{
	return isMove > 0 ? true : false;
}

Point MagicHero::getHeroMapPosition()
{
	return Point(getPositionX()/_BLOCK_SIZE_, getPositionY()/_BLOCK_SIZE_);
}

void MagicHero::moveHeroToOneDirection()
{
}

void MagicHero::stopHero()
{
	heroSprite->stopAction(moveAction);
	idleHero();
}

void MagicHero::incIsMove()
{
	isMove++;
}

void MagicHero::decIsMove()
{
	isMove--;
}

void MagicHero::setIsMoveToZero()
{
	isMove = 0;
	idleHero();
}

int MagicHero::getHeroDirect()
{
	return direct;
}

