#include "clientLayer.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace CocosDenshion;
bool clientLayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto sprite = Sprite::create("BeginScene2.png");

	sprite->setPosition(Vec2(winSize.width *0.5, winSize.height*0.5));
	this->addChild(sprite, 0);

	auto *menuItem = MenuItemImage::create("single1.png", "single2.png", CC_CALLBACK_1(clientLayer::menucallback, this));
	menuItem->setTag(101);
	menuItem->setPosition(Vec2(winSize.width *0.85, winSize.height*0.4));

	auto *menuItem_2 = MenuItemImage::create("double1.png", "double2.png", CC_CALLBACK_1(clientLayer::menucallback, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(winSize.width *0.85, winSize.height*0.3));

	auto *menuItem_3 = MenuItemImage::create("return1.png", "return2.png", CC_CALLBACK_1(clientLayer::menucallback, this));
	menuItem_3->setTag(103);
	menuItem_3->setPosition(Vec2(winSize.width *0.85, winSize.height*0.1));

	auto *menuItem_4 = MenuItemImage::create("return1.png", "return2.png", CC_CALLBACK_1(clientLayer::menucallback, this));
	menuItem_4->setTag(104);
	menuItem_4->setPosition(Vec2(winSize.width *0.85, winSize.height*0.2));

	auto menu = Menu::create(menuItem, menuItem_2, menuItem_3, menuItem_4,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	addSwitch();

	return true;
}
void clientLayer::menucallback(Ref *psender)
{
	static int time = 1;
	SimpleAudioEngine::getInstance()->playEffect("effect1.wav");
	switch (((MenuItem *)psender)->getTag())
	{
	case 101:
	{
		tsm->gochoosescene();
	}
	break;
	case 102:
	{
		tsm->gochoosescene(2,true);
	}
	break;
	case 103:
	{
		tsm->goLoadScene();
	}
	break;
	case 104:
	{
		if (time % 2 == 1) {
			Size winSize = Director::getInstance()->getWinSize();
			auto* rule = Sprite::create("rule.png");
			rule->setPosition(Vec2(winSize.width *0.5, winSize.height*0.5));
			rule->setScale(0.8);
			this->addChild(rule, 0,99);
		}else{
			this->removeChildByTag(99, true);
		}
		time++;
		break;
	}
	default:
		break;
	}
}