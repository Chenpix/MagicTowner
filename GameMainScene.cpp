#include "GameMainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

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
	//��ʼ������
	this->moveCount = 9;

	//��¼���ڴ�С
	this->winHeight = Director::getInstance()->getWinSize().height;
	this->winWidth = Director::getInstance()->getWinSize().width;

	//������Ƭ��ͼ�������ó�ʼλ��
	this->myTMXTiledMap = CCTMXTiledMap::create("room01.tmx");
	this->myTMXTiledMap->setAnchorPoint(Vec2(0, 0));
	this->myTMXTiledMap->setPosition(Vec2(winWidth / 2 - myTMXTiledMap->getMapSize().width*_BLOCK_SIZE_ / 2, winHeight / 2));
	this->addChild(myTMXTiledMap, 0);

	//��ʼ����ͼ��س�Ա����
	this->barrierLayer = this->myTMXTiledMap->layerNamed("Meta");
	barrierLayer->setVisible(false);
	this->mapHeight = myTMXTiledMap->getMapSize().height;
	this->mapWidth = myTMXTiledMap->getMapSize().width;

	//����Ӣ�۶��󣬰󶨵���ͼ�϶�Ӧ��objectλ��
	this->myMagicHero = MagicHero::getHeroInstance();
	this->myMagicHero->setAnchorPoint(Vec2(0, 0));
	this->objects = myTMXTiledMap->objectGroupNamed("obj");
	auto heroPoint = objects->getObject("hhh");

	int x = heroPoint["x"].asInt();
	int y = heroPoint["y"].asInt();

	myMagicHero->setPosition(Vec2(x, y));
	myTMXTiledMap->addChild(myMagicHero, 2);

	//��MainScene�ļ��̼�������ע������������󶨵�magicHero��
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
	}
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
	if (dir != -1) {//�ж��Ƿ�������Ч��

		//������ǵ�һ�ΰ��¼�����ֹ֮ͣǰ���˶�
		if (myMagicHero->isHeroMove()) {
			myMagicHero->stopHero();
		}
		this->myMagicHero->setHeroDirect(dir);
		this->myMagicHero->runAnimation(cocos2d::Size(72, 55));
		this->myMagicHero->incIsMove();
	}
}

void GameMainScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW || keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW
		|| keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		this->myMagicHero->decIsMove();
		if (!myMagicHero->isHeroMove()) {
			moveCount = 9;
			myMagicHero->stopHero();
		}
	}
}

bool GameMainScene::isHeroMoveAvailable()
{
	Vec2 deltaPos(myMagicHero->getHeroMapPosition().x, 20- myMagicHero->getHeroMapPosition().y);
	switch(myMagicHero->getHeroDirect()) 
	{
	case MagicHero::UP:
		deltaPos.y--;
		if (deltaPos.y < 0)
			return false;
		break;
	case MagicHero::DOWN:
		deltaPos.y++;
		if (deltaPos.y >= this->mapHeight)
			return false;
		break;
	case MagicHero::LEFT:
		deltaPos.x--;
		if (deltaPos.x < 0)
			return false;
		break;
	case MagicHero::RIGHT:
		deltaPos.x++;
		if (deltaPos.x >= this->mapWidth)
			return false;
		break;
	}
	//����ÿ�û����ײ���ͼ���Ƿ��ж���
	if (barrierLayer->tileAt(deltaPos) == 0) {
		dealObjects(objects, deltaPos);
	}
	return barrierLayer->tileAt(deltaPos) == 0 ? true : false;
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

bool GameMainScene::dealObjects(CCTMXObjectGroup* objects, Vec2 deltaPos)
{
	auto items = objects->getObjects();
	ValueVector temp;
	bool isFound = false;
	for (auto item : items) {
		auto values = item.asValueMap();
		if (!isFound && values["type"].asInt() != 0 &&
			values["x"].asInt() == deltaPos.x * 32 && 640 - values["y"].asInt() == deltaPos.y * 32) {
			myTMXTiledMap->getLayer("wall")->removeTileAt(deltaPos);
			auto temp = String::createWithFormat("��ϲ�����һ�� type Ϊ %d�ĵ���!", values["type"].asInt());
			auto string = G2U(temp->getCString());
			auto info = CCLabelTTF::create(string, "����", 35);
			info->setPosition(Vec2(winWidth / 2, winHeight / 2));
			info->setColor(Color3B(242, 19, 14));
			if (this->getChildByName("info") != NULL) {
				this->removeChildByName("info");
			}
			this->addChild(info, 2, "info");
			auto func = CCCallFunc::create(CC_CALLBACK_0(GameMainScene::removeLabel, this));
			auto fadeOut = CCFadeOut::create(2.0f);
			auto seq = CCSequence::createWithTwoActions(fadeOut, func);
			info->runAction(seq);
			delete[] string;
			printf("object has been removed\n");
		}
		else {
			temp.push_back(item);
		}
	}
	items.clear();
	objects->setObjects(temp);
	return false;
}

void GameMainScene::removeLabel()
{
	if (this->getChildByName("info") != NULL) {
		this->removeChildByName("info");
	}
}
