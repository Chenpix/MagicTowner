#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameMainScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Rect rect = Rect::ZERO;
	rect.size = Director::getInstance()->getWinSize();
	CCSprite* bg = CCSprite::create("game_bg.jpg", rect);
	bg->setAnchorPoint(Vec2(0, 0));
    addChild(bg);

	CCSprite* startButton = CCSprite::create("playGame.png");
	startButton->setPosition(Vec2(rect.size.width / 2, 2*rect.size.height / 6));
	addChild(startButton, 1, 1);

	/*CCSprite* introduceButton = CCSprite::create("gameintroduce.png");
	introduceButton->setPosition(Vec2(rect.size.width / 2, 2 * rect.size.height / 5));
	addChild(introduceButton, 1, 2);

	CCSprite* startButton = CCSprite::create("playGame.png");
	startButton->setPosition(Vec2(rect.size.width / 2, 2 * rect.size.height / 5));
	addChild(startButton, 1, 1);*/

	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(HelloWorld::mouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HelloWorld::mouseDown(Event *event) 
{
	EventMouse *e = (EventMouse*)event;
	printf("%f   %f   \n",e->getCursorX(), e->getCursorY());
	if (getChildByTag(1)->boundingBox().containsPoint(Vec2(e->getCursorX(), e->getCursorY())) )
	{
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, GameMainScene::createScene()));
	}
}