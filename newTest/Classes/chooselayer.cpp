#include "chooselayer.h"
bool chooselayer::init()
{
	

	return true;
};
void chooselayer::chooselayerInit() {
	Size winSize = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("chooselayerbg.png");
	sprite->setPosition(Vec2(winSize.width *0.5, winSize.height*0.5));
	this->addChild(sprite, 0);

	auto *menuItem = MenuItemImage::create("start1.png", "start2.png", CC_CALLBACK_1(chooselayer::menucallback, this));
	menuItem->setTag(101);
	menuItem->setPosition(Vec2(winSize.width *0.8, winSize.height*0.18));

	auto *menuItem_2 = MenuItemImage::create("return1.png", "return2.png", CC_CALLBACK_1(chooselayer::menucallback, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(winSize.width *0.8, winSize.height*0.08));


	auto menu = Menu::create(menuItem, menuItem_2, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);


	//MenuItemImage *map_1 = MenuItemImage::create("map1.png","map1_choose.png", CC_CALLBACK_1(chooselayer::mapcallback, this));
	//map_1->setTag(101);
	//map_1->setPosition(Director::getInstance()->convertToGL(Vec2(100, 500)));

	//auto mapmenu = Menu::create(map_1, NULL);
	//mapmenu->setPosition(Vec2::ZERO);
	//this->addChild(mapmenu);

	if (chooseNum == 2) {
		showFigureChoose(Vec2(246, 428));
		showFigureChoose(Vec2(656, 428), 300);
		showMapChoose(Vec2(winSize.width *0.5, 246));
	}
	else {
		showFigureChoose(Vec2(winSize.width * 0.5, 428));
		showMapChoose(Vec2(winSize.width *0.5, 246));
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
		_firmFigure->setTexture(_chooseFigure[0]);
	}
	break;
	case 102:
	{
		userOne = RED;
		_firmFigure->setTexture(_chooseFigure[1]);

	}

	break;
	case 103:
	{
		userOne = BLUE;
		_firmFigure->setTexture(_chooseFigure[2]);
	}
	break;
	case 104:
	{
		userOne = YELLOW;
		_firmFigure->setTexture(_chooseFigure[3]);
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
		_firmFigure2p->setTexture(_chooseFigure2p[0]);
	}
	break;
	case 302:
	{
		userTwo = RED;
		_firmFigure2p->setTexture(_chooseFigure2p[1]);
	}

	break;
	case 303:
	{
		userTwo = BLUE;
		_firmFigure2p->setTexture(_chooseFigure2p[2]);
	}
	break;
	case 304:
	{
		userTwo = YELLOW;
		_firmFigure2p->setTexture(_chooseFigure2p[3]);
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
			_firmMap->setTexture(_chooseMap[0]);
		}
		break;
		case 102:
		{
			map = 2;
			_firmMap->setTexture(_chooseMap[1]);
		}

		break;
		case 103:
		{
			map = 3;
			_firmMap->setTexture(_chooseMap[2]);
		}
		break;
		default:
			break;

		}
	}

void chooselayer::showFigureChoose(Point pos, float tag) {

	auto figurebg = Sprite::create("chooseFigurebg.png");
	figurebg->setPosition(Vec2(pos.x, pos.y));
	this->addChild(figurebg, 1);
	if (tag == 100) {
		_firmFigure = Sprite::create("chooseFigure1.png");
		_firmFigure->setPosition(Vec2(pos.x, pos.y + 110));
		this->addChild(_firmFigure, 3);
		_chooseFigure.push_back(TextureCache::sharedTextureCache()->addImage("chooseFigure1.png"));
		_chooseFigure.push_back(TextureCache::sharedTextureCache()->addImage("chooseFigure2.png"));
		_chooseFigure.push_back(TextureCache::sharedTextureCache()->addImage("chooseFigure3.png"));
		_chooseFigure.push_back(TextureCache::sharedTextureCache()->addImage("chooseFigure4.png"));
	}

	if (tag == 300) {
		_firmFigure2p = Sprite::create("chooseFigure2p1.png");
		_firmFigure2p->setPosition(Vec2(pos.x, pos.y + 110));
		this->addChild(_firmFigure2p, 3);
		_chooseFigure2p.push_back(TextureCache::sharedTextureCache()->addImage("chooseFigure2p1.png"));
		_chooseFigure2p.push_back(TextureCache::sharedTextureCache()->addImage("chooseFigure2p2.png"));
		_chooseFigure2p.push_back(TextureCache::sharedTextureCache()->addImage("chooseFigure2p3.png"));
		_chooseFigure2p.push_back(TextureCache::sharedTextureCache()->addImage("chooseFigure2p4.png"));
	}
	MenuItemImage *figure_1 = MenuItemImage::create("friend_00.png", "", CC_CALLBACK_1(chooselayer::figurecallback, this));
	figure_1->setTag(tag + 1);
	figure_1->setPosition(Vec2(pos.x - 150, pos.y));


	MenuItemImage *figure_2 = MenuItemImage::create("friend_01.png", "", CC_CALLBACK_1(chooselayer::figurecallback, this));
	figure_2->setTag(tag + 2);
	figure_2->setPosition(Vec2(pos.x - 50, pos.y));


	MenuItemImage *figure_3 = MenuItemImage::create("friend_03.png", "", CC_CALLBACK_1(chooselayer::figurecallback, this));
	figure_3->setTag(tag + 3);
	figure_3->setPosition(Vec2(pos.x + 50, pos.y));


	MenuItemImage *figure_4 = MenuItemImage::create("friend_05.png", "", CC_CALLBACK_1(chooselayer::figurecallback, this));
	figure_4->setTag(tag + 4);
	figure_4->setPosition(Vec2(pos.x + 150, pos.y));


	auto figuremenu = Menu::create(figure_1, figure_2, figure_3, figure_4, NULL);
	figuremenu->setPosition(Vec2::ZERO);
	this->addChild(figuremenu, 2);

}

void chooselayer::showMapChoose(Point pos) {
	auto mapbg = Sprite::create("chooseMapbg.png");
	mapbg->setPosition(pos);
	this->addChild(mapbg, 1);

	_firmMap = Sprite::create("chooseMap1.png");
	_firmMap->setPosition(Vec2(pos.x, pos.y - 10));
	this->addChild(_firmMap, 3);
	_chooseMap.push_back(TextureCache::sharedTextureCache()->addImage("chooseMap1.png"));
	_chooseMap.push_back(TextureCache::sharedTextureCache()->addImage("chooseMap2.png"));
	_chooseMap.push_back(TextureCache::sharedTextureCache()->addImage("chooseMap3.png"));
	

	MenuItemImage *map_1 = MenuItemImage::create("map1.png", "", CC_CALLBACK_1(chooselayer::mapcallback, this));
	map_1->setTag(101);
	map_1->setPosition(Vec2(pos.x - 203, pos.y));

	MenuItemImage *map_2 = MenuItemImage::create("map2.png", "", CC_CALLBACK_1(chooselayer::mapcallback, this));
	map_2->setTag(102);
	map_2->setPosition(Vec2(pos.x, pos.y));

	MenuItemImage *map_3 = MenuItemImage::create("map3.png", "", CC_CALLBACK_1(chooselayer::mapcallback, this));
	map_3->setTag(103);
	map_3->setPosition(Vec2(pos.x + 203, pos.y));

	auto mapmenu = Menu::create(map_1, map_2, map_3, NULL);
	mapmenu->setPosition(Point::ZERO);
	this->addChild(mapmenu, 2);
	
}