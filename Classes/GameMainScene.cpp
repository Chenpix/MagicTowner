#include "GameMainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool isLoadingMXL = false;

Scene* GameMainScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameMainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameMainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//初始化计数
	this->moveCount = 9;
	this->fightCount = 50;

	//记录窗口大小
	this->winHeight = Director::getInstance()->getWinSize().height;
	this->winWidth = Director::getInstance()->getWinSize().width;

	//生成瓦片地图对象并设置初始位置
	this->myTMXTiledMap = CCTMXTiledMap::create("room/room01.tmx");
	this->myTMXTiledMap->setAnchorPoint(Vec2(0, 0));
	this->myTMXTiledMap->setPosition(Vec2(winWidth / 2 - myTMXTiledMap->getMapSize().width*_BLOCK_SIZE_ / 2, winHeight / 2));
	this->addChild(myTMXTiledMap, 0);

	//初始化地图相关成员变量
	this->barrierLayer = this->myTMXTiledMap->layerNamed("Meta");
	barrierLayer->setVisible(false);
	this->mapHeight = myTMXTiledMap->getMapSize().height;
	this->mapWidth = myTMXTiledMap->getMapSize().width;

	//生成英雄对象，绑定到地图上对应的object位置
	this->myMagicHero = MagicHero::getHeroInstance();
	this->myMagicHero->setAnchorPoint(Vec2(0, 0));
	this->objects = myTMXTiledMap->getObjectGroup("obj");
	auto heroPoint = objects->getObject("HERO");

	int x = heroPoint["x"].asInt();
	int y = heroPoint["y"].asInt();

	myMagicHero->setPosition(Vec2(x, y));
	myTMXTiledMap->addChild(myMagicHero, 2);

	//生成英雄状态栏
	statusBar = new HeroStatusBar();
	statusBar->autorelease();
	statusBar->setContentSize(Size(winWidth, 3*_BLOCK_SIZE_));
	statusBar->setAnchorPoint(Vec2(0, 0));
	statusBar->setPosition(0, winHeight - 3 * _BLOCK_SIZE_);
	this->addChild(statusBar, 1, "STATUS");

	//将MainScene的键盘监听函数注册监听器，并绑定到magicHero上
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameMainScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameMainScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, myMagicHero);

	this->scheduleUpdate();
	return true;
}

void GameMainScene::update(float delta) 
{
	if (myMagicHero->isHeroMove())
	{
		moveCount++;
		if (moveCount >= 10 && isHeroMoveAvailable()) {
			moveCount = 0;
			Vec2 v = myMagicHero->moveHeroStep();
 			myTMXTiledMap->setPosition(myTMXTiledMap->getPosition() - v);
			//printf("hero position x:%f , y:%f\n", magicHero->getPositionX(), magicHero->getPositionY());
		}
		//加载词典，放在英雄移动函数中，只运行一次。（不放在init函数中是为了提高加载速度）
		if (!isLoadingMXL) {
			printf("size of xml is %d \n", sizeof(monsters));
			monsters = FileUtils::getInstance()->getValueVectorFromFile("data/monster.plist");
			isLoadingMXL = true;
			printf("size of xml is %d \n", sizeof(monsters));
		}
	}
	else if (myMagicHero->isHeroFighting()) {//战斗状态
		fightCount++;
		if (fightCount >= 30) {
			fightCount = 0;
			switch (heroFightTurn)
			{
			case true:
			{
				int dec = currMonster->lessenHP(statusBar->getHeroAttack());
				if (dec == -1) {
					showMessage(_MESSAGE_SYSTEM_, String::create("恭喜你击败了敌人！"), true);
					delete currMonster;
					currMonster = nullptr;
					myMagicHero->setFightStatus(false);
					heroFightTurn = true;
					_eventDispatcher->setEnabled(true);
					myTMXTiledMap->getLayer("wall")->removeTileAt(getDeltaPostion());
				}
				else {
					showMessage(_MESSAGE_MONSTER_LOSS_HP_, String::createWithFormat("HP-%d", dec), false);
					heroFightTurn = false;
				}
				break;
			}
			case false: 
			{
				int dec = statusBar->lessenHP(currMonster->getMonsterAttack());
				if (dec == 0) {
					showMessage(_MESSAGE_HERO_LOSS_HP_, String::create("你未受到伤害！"), true);
					heroFightTurn = true;
				}
				else if (dec == -1) {
					showMessage(_MESSAGE_SYSTEM_, String::create("年轻的勇士啊，你需要更多的历练，请重新踏上征途吧！"), true);
				}
				else {
					showMessage(_MESSAGE_HERO_LOSS_HP_, String::createWithFormat("HP-%d", dec), false);
					heroFightTurn = true;
				}
				break;
			}
			default:
				break;
			}
		}
	}
}

GameMainScene::~GameMainScene()
{
	/*this->statusBar->release();
	this->objects->release();
	this->barrierLayer->release();
	this->myTMXTiledMap->release();*/
	this->removeAllChildren();
	this->release();
}

void GameMainScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	int dir = -1;
	int exdir = myMagicHero->getHeroDirect();
	
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		//hero move up
		dir = MagicHero::UP;
		//magicHero
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		//hero move down
		dir = MagicHero::DOWN;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		//hero move left
		dir = MagicHero::LEFT;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		//hero move right
		dir = MagicHero::RIGHT;
		break;
	default:
		break;
	}
	if (dir != -1) {//判断是否按下了有效键

		//如果不是第一次按下键，就停止之前的运动
		if (myMagicHero->isHeroMove()) {
			myMagicHero->stopHero();
		}
		this->myMagicHero->setHeroDirect(dir);
		this->myMagicHero->runAnimation();
		this->myMagicHero->incIsMove();
	}
}

void GameMainScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW || keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW
		|| keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		if (this->myMagicHero->isHeroMove()) {
			this->myMagicHero->decIsMove();
			if (!myMagicHero->isHeroMove()) {
				moveCount = 9;
				myMagicHero->stopHero();
			}
		}
	}
}

bool GameMainScene::isHeroMoveAvailable()
{
	Vec2 deltaPos = getDeltaPostion();
	if (deltaPos.x == -1 && deltaPos.y == -1) {
		return false;
	}

	//如果该块没有碰撞，就检测是否有对象
	if (barrierLayer->tileAt(deltaPos) == 0) {
		return dealObjects(objects, deltaPos);
	}
	return false;
}

char* GameMainScene::G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) 
		delete[] wstr;
	return str;
}

int GameMainScene::dealObjects(CCTMXObjectGroup* objects, Vec2 deltaPos)
{
	auto items = objects->getObjects();
	ValueVector temp;
	
	bool isFound = false;
	for (auto item : items) {
		auto values = item.asValueMap();
		if (!isFound && values["type"].asInt() != 0 && myTMXTiledMap->getLayer("wall")->tileAt(deltaPos) != 0 &&
			values["x"].asInt() == deltaPos.x * 32 && 640 - values["y"].asInt() == deltaPos.y * 32) {

			isFound = true;
			if (dealInterAction(values)) {
				myTMXTiledMap->getLayer("wall")->removeTileAt(deltaPos);
			}
			break;
		}
	}
	return !isFound;
}

void GameMainScene::removeLabel(CCNode* sender, const char* name)
{
	if (this->getChildByName(name) != NULL) {
		this->removeChildByName(name);
	}
}

void GameMainScene::showMessage(int type, String* message, bool isChinese)
{
	char* string = nullptr;

	//是否要做中文转化
	if (isChinese) {
		string = G2U(message->getCString());
	}
	else {
		string = new char[strlen(message->getCString())+1];
		strcpy(string, message->getCString());
	}

	CCLabelTTF* info = NULL;
	CCFiniteTimeAction* firstAction = NULL;
	switch (type)
	{
	case _MESSAGE_SYSTEM_:
		info = CCLabelTTF::create(string, "华文琥珀", 40);
		info->setPosition(Vec2(winWidth / 2, winHeight*3 / 4));
		info->setColor(Color3B(242, 19, 14));
		firstAction = CCFadeOut::create(2.0f);
		break;
	case _MESSAGE_HERO_LOSS_HP_:
	case _MESSAGE_MONSTER_LOSS_HP_:
		info = CCLabelTTF::create(string, "华文行楷", 18);
		info->setPosition(convertToWorldSpace(myMagicHero->getParent()->convertToWorldSpace(myMagicHero->getPosition())) + Vec2(20, 60));
		info->setColor(Color3B(255, 255, 0));
		if (type == _MESSAGE_MONSTER_LOSS_HP_) {
			switch (myMagicHero->getHeroDirect())
			{
			case MagicHero::UP:
				info->setPositionY(info->getPositionY() + _BLOCK_SIZE_);
				break;
			case MagicHero::DOWN:
				info->setPositionY(info->getPositionY() - _BLOCK_SIZE_);
				break;
			case MagicHero::LEFT:
				info->setPositionY(info->getPositionY() - _BLOCK_SIZE_);
				break;
			case MagicHero::RIGHT:
				info->setPositionY(info->getPositionY() + _BLOCK_SIZE_);
				break;
			default:
				break;
			}
			info->setColor(Color3B(239, 7, 239));
		}
		firstAction = CCJumpTo::create(1.5f, info->getPosition()+Vec2(32, 20), 20, 2);
		break;
	default:
		break;
	}
	
	if (this->getChildByName(InfoName[type]) != NULL) {
		this->removeChildByName(InfoName[type]);
	}
	this->addChild(info, 3, InfoName[type]);
	auto func = CCCallFuncN::create(CC_CALLBACK_1(GameMainScene::removeLabel, this, InfoName[type]));
	auto seq = CCSequence::createWithTwoActions(firstAction, func);
	info->runAction(seq);
	delete[] string;
	string = NULL;
}

cocos2d::Vec2 GameMainScene::getDeltaPostion()
{
	Vec2 deltaPos(myMagicHero->getHeroMapPosition().x, 20 - myMagicHero->getHeroMapPosition().y);
	switch (myMagicHero->getHeroDirect())
	{
	case MagicHero::UP:
		deltaPos.y--;
		if (deltaPos.y < 0)
			deltaPos = Vec2(-1, -1);
		break;
	case MagicHero::DOWN:
		deltaPos.y++;
		if (deltaPos.y >= this->mapHeight)
			deltaPos = Vec2(-1, -1);
		break;
	case MagicHero::LEFT:
		deltaPos.x--;
		if (deltaPos.x < 0)
			deltaPos = Vec2(-1, -1);
		break;
	case MagicHero::RIGHT:
		deltaPos.x++;
		if (deltaPos.x >= this->mapWidth)
			deltaPos = Vec2(-1, -1);
		break;
	}
	return deltaPos;
}

bool GameMainScene::dealInterAction(cocos2d::ValueMap vmap)
{
	int type = vmap["type"].asInt();
	switch (type)
	{
	case 0: //HERO
		
		break;
	case 1: //NPC

		return false;
	case 2: //MONSTER
	{
		auto datas = monsters.at(vmap["index"].asInt()).asValueMap();
		if (statusBar->getHeroAttack() > datas["defend"].asInt()) {
			//进入战斗状态
			auto information = datas["information"].asString();
			auto info = CCLabelTTF::create(information, "华文琥珀", 40);
			info->setPosition(Vec2(winWidth / 2, winHeight * 4 / 5));
			info->setColor(Color3B(153, 0, 0));
			this->addChild(info, 3, "WELCOME");
			auto seq = CCSequence::createWithTwoActions(CCBlink::create(3, 3), CCCallFunc::create([&]() {
				this->removeChildByName("WELCOME");
				myMagicHero->setFightStatus(true);
			}));
			info->runAction(seq);

			myMagicHero->setIsMoveToZero();
			currMonster = new MagicMonster(datas);
			_eventDispatcher->setEnabled(false);
		}
		else {
			showMessage(_MESSAGE_SYSTEM_, String::create("年轻的勇者啊，你不是敌人的对手，赶紧回去吧！"), true);
		}
		return false;
	}
	case 3: //ITEM

		break;
	case 4: //DOOR

		break;
	default:
		break;
	}
	return true;
}
