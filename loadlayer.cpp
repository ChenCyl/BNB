#include "loadlayer.h"
#include "cocos2d.h"
#include "curl/curl.h"
USING_NS_CC;
using namespace cocos2d;
bool loadlayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();

   /* auto label = Label::createWithSystemFont("Game","",32);
    label->setPosition(Vec2(220, 220));
	this->addChild(label,1);//¼ÓÔØ³¡¾°*/


	auto sprite = Sprite::create("BeginScene2.png");

	sprite->setPosition(Vec2(winSize.width *0.5, winSize.height*0.5));
	this->addChild(sprite,0);



	MenuItemLabel *menuItem = MenuItemLabel::create(Label::createWithSystemFont("Start","", 30), CC_CALLBACK_1(loadlayer::menucallback, this));
	menuItem->setColor(Color3B(0, 0, 0));
	menuItem->setTag(101);
	menuItem->setPosition(Vec2(winSize.width *0.8, winSize.height*0.2));

	MenuItemLabel *menuItem_2 = MenuItemLabel::create(Label::createWithSystemFont("Return","", 30), CC_CALLBACK_1(loadlayer::menucallback, this));
	menuItem_2->setColor(Color3B(0, 0, 0));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(winSize.width *0.8, winSize.height*0.1));

	auto menu = Menu::create(menuItem, menuItem_2, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	    
		
    return true;
}
void loadlayer::menucallback(Ref *psender)
{
	switch(((MenuItem *)psender)->getTag())
	{
	case 101:
	{
		tsm->goserverscene();
	}
		break;
	case 102:
	{
		Director::getInstance()->end();
		exit(0);
	}

		break;

	default:
		break;
 


	}




}



