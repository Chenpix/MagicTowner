#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "MagicHero.h"
#include "HeroStatusBar.h"
#include "MagicMonster.h"

#define _MESSAGE_SYSTEM_ 0
#define _MESSAGE_HERO_LOSS_HP_ 1
#define _MESSAGE_MONSTER_LOSS_HP_ 2

class GameMainScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	static char* G2U(const char* gb2312);//����UTF-8�ַ�ת������

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameMainScene);

	MagicHero *myMagicHero;

	void update(float delta);
	~GameMainScene();
private:

	//��Ϸ��ͼ�ļ�
	cocos2d::CCTMXTiledMap *myTMXTiledMap;
	cocos2d::CCTMXLayer *barrierLayer;

	//������Ӧ����
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);

	bool isHeroMoveAvailable();//�ж�Ӣ���Ƿ�����ƶ�
	int dealObjects(cocos2d::CCTMXObjectGroup* objects, cocos2d::Vec2 position);
	void removeLabel(cocos2d::CCNode* sender, const char* name);//��ʾ���Ƴ�label�ؼ�
	void showMessage(int type, cocos2d::String* message, bool isChinese);//��ʾ��Ϣ,type��Ӧ��Ϣ����
	cocos2d::Vec2 getDeltaPostion();
	bool dealInterAction(cocos2d::ValueMap vmap);

	int winHeight, winWidth;//��Ϸ���ڴ�С
	int mapHeight, mapWidth;//��Ϸ��ͼ��С
	int moveCount;//�ƶ�������ʹӢ���ƶ�����ƽ��
	int fightCount;//ս��������ʹս���غ��ƽ���
	bool heroFightTurn;//�ж��Ƿ���Ӣ�۵Ļغ�

	const char* InfoName[3] = { "TIPS","DECHP", "DECHP" };

	cocos2d::TMXObjectGroup* objects;//��ǰ��ͼ�Ŀɻ�������Ӣ�ۼ���
	cocos2d::ValueVector monsters;//�������ݴʵ�
	MagicMonster* currMonster;//��ǰս������
	HeroStatusBar* statusBar;
};

#endif