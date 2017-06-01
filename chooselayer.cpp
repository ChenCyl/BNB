#include "chooselayer.h"
bool chooselayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("bg2.png");
	sprite->setPosition(Vec2(winSize.width *0.5, winSize.height*0.43));
	this->addChild(sprite, 0);

    /*auto label = Label::createWithSystemFont("choose map and character", "", 32);
	label->setPosition(Vec2(winSize.width *0.5, winSize.height*0.5));
	this->addChild(label, 1);*/

	MenuItemLabel *menuItem = MenuItemLabel::create(Label::createWithSystemFont("Continue", "", 30), CC_CALLBACK_1(chooselayer::menucallback, this));
	menuItem->setTag(101);
	menuItem->setPosition(Vec2(winSize.width *0.8, winSize.height*0.3));

	MenuItemLabel *menuItem_2 = MenuItemLabel::create(Label::createWithSystemFont("Return", "", 30), CC_CALLBACK_1(chooselayer::menucallback, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(winSize.width *0.8, winSize.height*0.15));


	auto menu = Menu::create(menuItem, menuItem_2, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

    MenuItemImage *figure_1 = MenuItemImage::create("friend_00.png","friend_00_choose.png",CC_CALLBACK_1(chooselayer::figurecallback, this));
	figure_1->setTag(101);
	figure_1->setPosition(Director::getInstance()->convertToGL(Vec2(100,100)));
	

	MenuItemImage *figure_2 = MenuItemImage::create("friend_01.png", "friend_01_choose.png", CC_CALLBACK_1(chooselayer::figurecallback, this));
	figure_2->setTag(102);
	figure_2->setPosition(Director::getInstance()->convertToGL(Vec2(300,100)));
	

	MenuItemImage *figure_3 = MenuItemImage::create("friend_03.png", "friend_03_choose.png", CC_CALLBACK_1(chooselayer::figurecallback, this));
	figure_3->setTag(103);
	figure_3->setPosition(Director::getInstance()->convertToGL(Vec2(500, 100)));
	

	MenuItemImage *figure_4 = MenuItemImage::create("friend_05.png", "friend_05_choose.png", CC_CALLBACK_1(chooselayer::figurecallback, this));
	figure_4->setTag(104);
	figure_4->setPosition(Director::getInstance()->convertToGL(Vec2(700, 100)));
	

	auto figuremenu = Menu::create(figure_1,figure_2, figure_3 , figure_4, NULL);
	figuremenu->setPosition(Vec2::ZERO);
	this->addChild(figuremenu);

	MenuItemImage *map_1 = MenuItemImage::create("map1.png", "map1_choose.png", CC_CALLBACK_1(chooselayer::mapcallback, this));
	map_1->setTag(101);
	map_1->setPosition(Director::getInstance()->convertToGL(Vec2(100, 400)));

	auto mapmenu = Menu::create( map_1, NULL);
	mapmenu->setPosition(Vec2::ZERO);
	this->addChild(mapmenu);


	return true;
};

void chooselayer::menucallback(Ref *psender)
{
	switch (((MenuItem *)psender)->getTag())
	{
	case 101:
	{
		tsm->gogamescene(user,map);
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
void chooselayer::figurecallback(Ref *psender)
{
	switch (((MenuItemImage *)psender)->getTag())
	{
	case 101:
	{
		user = 1;
	}
	break;
	case 102:
	{
		user = 2;
	}

	break;
	case 103:
	{
		user = 3;
	}
	break;
	case 104:
	{
		user = 4;
	}
	break;

	default:
		break;

	}
}

void chooselayer::mapcallback(Ref *psender)
{
		switch (((MenuItemImage *)psender)->getTag())
		{
		case 101:
		{
			map= 1;
		}
		break;
		case 102:
		{
			map = 2;
		}

		break;
		case 103:
		{
		map = 3;
		}
		break;
		case 104:
		{
			map = 4;
		}
		break;

		default:
			break;

		}
	}




