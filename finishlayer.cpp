#include "finishlayer.h"
bool finishlayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto sprite = Sprite::create("finishscene.png");
	sprite->setPosition(Vec2(winSize.width *0.5, winSize.height*0.5));
	this->addChild(sprite, 0);

	auto label = Label::createWithSystemFont("Thank you", "", 50);
	label->setColor(Color3B(0, 0, 0));
	label->setPosition(Vec2(winSize.width *0.5, winSize.height*0.8));
	this->addChild(label, 1);

	

	MenuItemLabel *menuItem = MenuItemLabel::create(Label::createWithSystemFont("Again", "", 30), CC_CALLBACK_1(finishlayer::menucallback, this));
	menuItem->setTag(101);
	menuItem->setPosition(Vec2(winSize.width *0.8, winSize.height*0.3));

	MenuItemLabel *menuItem_2 = MenuItemLabel::create(Label::createWithSystemFont("Exit", "", 30), CC_CALLBACK_1(finishlayer::menucallback, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(winSize.width *0.8, winSize.height*0.15));

	auto menu = Menu::create(menuItem, menuItem_2, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	return true;
};
void finishlayer::menucallback(Ref *psender)
{
	switch (((MenuItem *)psender)->getTag())
	{
	case 101:
	{
		tsm->gochoosescene();
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