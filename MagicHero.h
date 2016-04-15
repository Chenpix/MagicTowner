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
	bool isHeroMove();

	//��ȡӢ�۵�ͼ����
	cocos2d::Point getHeroMapPosition();

	//Ӣ���ƶ�����
	void idleHero();
	void runAnimation(cocos2d::Size texSize);
	void moveHeroToOneDirection();
	void stopHero();

private:
	MagicHero(int hp, int level);
	int maxHP; // Ӣ�۵�ǰ���Ѫ��
	int hp; //Ӣ�۵�ǰѪ��
	int direct;//Ӣ�۵�ǰ�泯����
	int EXP;//Ӣ�۵�ǰ����ֵ
	int maxEXP; // Ӣ�۵�ǰ�ȼ������ֵ
	int level;//Ӣ�۵�ǰ�ȼ�
	int pRoom;//���ڷ���
	int isMove;//Ӣ���Ƿ����ƶ�
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