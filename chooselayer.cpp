#include "chooselayer.h"
bool chooselayer::init()
{
	

	return true;
};
void chooselayer::chooselayerInit() {
	Size winSize = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("bg2.png");
	sprite->setPosition(Vec2(winSize.width *0.5, winSize.height*0.43));
	this->addChild(sprite, 0);


	MenuItemLabel *menuItem = MenuItemLabel::create(Label::createWithSystemFont("Start", "", 30), CC_CALLBACK_1(chooselayer::menucallback, this));
	menuItem->setTag(101);
	menuItem->setPosition(Vec2(winSize.width *0.8, winSize.height*0.3));

	MenuItemLabel *menuItem_2 = MenuItemLabel::create(Label::createWithSystemFont("Return", "", 30), CC_CALLBACK_1(chooselayer::menucallback, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(winSize.width *0.8, winSize.height*0.15));


	auto menu = Menu::create(menuItem, menuItem_2, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);


	MenuItemImage *map_1 = MenuItemImage::create("map1.png", "map1_choose.png", CC_CALLBACK_1(chooselayer::mapcallback, this));
	map_1->setTag(101);
	map_1->setPosition(Director::getInstance()->convertToGL(Vec2(100, 500)));

	auto mapmenu = Menu::create(map_1, NULL);
	mapmenu->setPosition(Vec2::ZERO);
	this->addChild(mapmenu);

	showFigureChoose();
	if (chooseNum == 2) {
		showFigureChoose(300);
	}
}
void chooselayer::menucallback(Ref *psender)
{
	switch (((MenuItem *)psender)->getTag())
	{
	case 101:
	{
		tsm->gogamescene(chooseNum,userOne,userTwo,map,this,isClient);
	}
	break;
	case 102:
	{
		if (isClient) {
			tsm->goClientScene();
		}
		else {
			tsm->goserverscene();
		}
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
		userOne = GREEN;
	}
	break;
	case 102:
	{
		userOne = RED;
	}

	break;
	case 103:
	{
		userOne = BLUE;
	}
	break;
	case 104:
	{
		userOne = YELLOW;
	}
	break;
	default:
		break;
	}
	switch (((MenuItemImage *)psender)->getTag())
	{
	case 301:
	{
		userTwo = GREEN;
	}
	break;
	case 302:
	{
		userTwo = RED;
	}

	break;
	case 303:
	{
		userTwo = BLUE;
	}
	break;
	case 304:
	{
		userTwo = YELLOW;
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

void chooselayer::showFigureChoose(float y) {

	MenuItemImage *figure_1 = MenuItemImage::create("friend_00.png", "friend_00_choose.png", CC_CALLBACK_1(chooselayer::figurecallback, this));
	figure_1->setTag(y+1);
	figure_1->setPosition(Director::getInstance()->convertToGL(Vec2(100, y)));


	MenuItemImage *figure_2 = MenuItemImage::create("friend_01.png", "friend_01_choose.png", CC_CALLBACK_1(chooselayer::figurecallback, this));
	figure_2->setTag(y+2);
	figure_2->setPosition(Director::getInstance()->convertToGL(Vec2(300, y)));


	MenuItemImage *figure_3 = MenuItemImage::create("friend_03.png", "friend_03_choose.png", CC_CALLBACK_1(chooselayer::figurecallback, this));
	figure_3->setTag(y+3);
	figure_3->setPosition(Director::getInstance()->convertToGL(Vec2(500, y)));


	MenuItemImage *figure_4 = MenuItemImage::create("friend_05.png", "friend_05_choose.png", CC_CALLBACK_1(chooselayer::figurecallback, this));
	figure_4->setTag(y+4);
	figure_4->setPosition(Director::getInstance()->convertToGL(Vec2(700, y)));


	auto figuremenu = Menu::create(figure_1, figure_2, figure_3, figure_4, NULL);
	figuremenu->setPosition(Vec2::ZERO);
	this->addChild(figuremenu);

}