#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "MagicHero.h"

class GameMainScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameMainScene);

	MagicHero *myMagicHero;

	void update(float delta);

private:

	//��Ϸ��ͼ�ļ�
	cocos2d::CCTMXTiledMap *myTMXTiledMap;
	cocos2d::CCTMXLayer *barrierLayer;

	//������Ӧ����
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);

	bool isHeroMoveAvailable();//�ж�Ӣ���Ƿ�����ƶ�
	char* G2U(const char* gb2312);//����UTF-8�ַ�ת������
	bool dealObjects(cocos2d::CCTMXObjectGroup* objects, cocos2d::Vec2 position);
	void removeLabel();//��ʾ���Ƴ�label�ؼ�

	int winHeight, winWidth;//��Ϸ���ڴ�С
	int mapHeight, mapWidth;//��Ϸ��ͼ��С
	int moveCount;//�ƶ�������ʹӢ���ƶ�����ƽ��

	cocos2d::TMXObjectGroup* objects;
};

#endif