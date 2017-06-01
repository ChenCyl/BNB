#include "gamelayer.h"
bool gamelayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();


	MenuItemLabel *menuItem = MenuItemLabel::create(Label::createWithSystemFont("finish ", "", 30), CC_CALLBACK_1(gamelayer::menucallback, this));
	menuItem->setTag(101);
	menuItem->setPosition(Vec2(winSize.width *0.8, winSize.height*0.3));

	MenuItemLabel *menuItem_2 = MenuItemLabel::create(Label::createWithSystemFont("Again", "", 30), CC_CALLBACK_1(gamelayer::menucallback, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(winSize.width *0.8, winSize.height*0.15));

	auto menu = Menu::create(menuItem, menuItem_2, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);


	

	auto sprite = Sprite::create("gamemap1.png");
	sprite->setPosition(Vec2(winSize.width *0.34, winSize.height*0.5));
	this->addChild(sprite, 0);

	

	return true;
};
void gamelayer::menucallback(Ref *psender)
{
	switch (((MenuItem *)psender)->getTag())
	{
	case 101:
	{
		tsm->gofinishscene();
	}
	break;
	case 102:
	{
		tsm->gochoosescene();
	}

	break;

	default:
		break;

	}
}

