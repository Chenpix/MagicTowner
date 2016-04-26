#ifndef __HERO__H_
#define __HERO__H_

#include "cocos2d.h"

#define _BLOCK_SIZE_ 32

class MagicHero : public cocos2d::CCSprite
{
public:
	~MagicHero();

	static MagicHero* getHeroInstance();

	const static int UP = 0;
	const static int DOWN = 1;
	const static int LEFT = 2;
	const static int RIGHT = 3;

	//�ƶ�һ�񣬷���һ���ƶ�λ��ƫ����
	cocos2d::Vec2 moveHeroStep();

	//����Ӣ�۷���
	void setHeroDirect(int dir);
	int getHeroDirect();

	//Ӣ���ƶ���ز���
	void incIsMove();
	void decIsMove();
	void setIsMoveToZero();
	bool isHeroMove();

	//��ȡӢ�۵�ͼ����
	cocos2d::Point getHeroMapPosition();

	//Ӣ���ƶ�����
	void idleHero();
	void runAnimation();
	void moveHeroToOneDirection();
	void stopHero();
	
	//Ӣ��ս�����
	void setFightStatus(bool isFighting);
	bool isHeroFighting();

private:
	MagicHero();
	int direct;//Ӣ�۵�ǰ�泯����
	int pRoom;//���ڷ���
	int isMove;//Ӣ���Ƿ����ƶ�
	bool isFighting;//Ӣ���Ƿ���ս��
	//Vector<int> bag;//Ӣ�����ﱳ��

	//Ӣ�۵���
	static MagicHero* heroInstance;

	cocos2d::Sprite *heroSprite;//Ӣ�۾���

	//��ʼ��Ӣ��animation
	void initSpriteAndAnimation();

	//Ӣ�۶���
	cocos2d::Action *moveAction;

	char* idel[4];

	class Garbo
	{
	public:
		Garbo();
		~Garbo() {
			if (heroInstance != NULL)
			{
				delete MagicHero::heroInstance;
			}
		}

	};

	//����������������̬�����ᱻ����
	static Garbo garbo;
};

#endif // !__HERO__H_