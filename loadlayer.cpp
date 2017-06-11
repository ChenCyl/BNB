#include "loadlayer.h"
#include "cocos2d.h"
#include "Switch.h"
USING_NS_CC;
using namespace cocos2d;
bool loadlayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto sprite = Sprite::create("BeginScene2.png");

	sprite->setPosition(Vec2(winSize.width *0.5, winSize.height*0.5));
	this->addChild(sprite,0);

	auto *menuItem = MenuItemImage::create("client1.png", "client2.png", CC_CALLBACK_1(loadlayer::menucallback, this));
	//color
	menuItem->setTag(101);
	menuItem->setPosition(Vec2(winSize.width *0.8, winSize.height*0.2));

	auto *menuItem_2 = MenuItemImage::create("server1.png", "server2.png", CC_CALLBACK_1(loadlayer::menucallback, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(winSize.width *0.8, winSize.height*0.1));

	auto menu = Menu::create(menuItem, menuItem_2, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	auto* mySwitch = Switch::createSwitch(1, 0, false);
	addChild(mySwitch);
	return true;
}
void loadlayer::menucallback(Ref *psender)
{
	switch(((MenuItem *)psender)->getTag())
	{
	case 101:
	{
		tsm->goClientScene();
	}
		break;
	case 102:
	{
		tsm->goserverscene();
	}

		break;

	default:
		break;
	}
}