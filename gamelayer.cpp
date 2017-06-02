#include "gamelayer.h"
#include "SimpleAudioEngine.h"
#include "Player_one.h"
#include "Player_se.h"
#include <math.h>
#include <iterator>
#include <algorithm>
#include <numeric>

USING_NS_CC;

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

	loadMap();
	loadFigure();

	

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

void gamelayer::loadMap() {
	Size winSize = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create("gamemap1.png");
	sprite->setPosition(Vec2(winSize.width *0.34, winSize.height*0.5));
	this->addChild(sprite, 0);
	
}

void gamelayer::loadFigure() {
	Size winSize = Director::getInstance()->getWinSize();
	Point mapSize = Vec2(winSize.width *0.34, winSize.height*0.5);
	
	for (int i = 0;i < playerOne;i++) {
		Player_one* player1 = Player_one::createFigureSprite(Vec2(mapSize.x/2+25,
			mapSize.y/ 2 + 50), DOWN, USER, BLUE, 0);
		player1->myGamelayer = this;
		players.push_back(player1);
		addChild(player1, 3);
	}
	for (int i = 0;i < playerSe;i++) {
		Player_se* player2 = Player_se::createFigureSprite(Vec2(mapSize.x / 2 - 25,
			mapSize.y / 2 + 50), DOWN, USER, RED, 1);
		player2->myGamelayer = this;
		players.push_back(player2);
		addChild(player2, 3);
	}
}

void gamelayer::figureMove(int tag, int direction) {
	bool canMove = true;
	players[tag]->Move(direction, (canMove&&moveifPlayer(tag)));

}

void gamelayer::putBomb(int playerTag, Point position) {
	Point mP = players[playerTag]->position;//转换坐标
	int bombPower = players[playerTag]->bombPower;
	auto myBomb = Bomb::createBombSprite(mP);
	myBomb->myGamelayer = this;
	addChild(myBomb, 1);
	myBomb->bombDynamic();
	std::vector<Point> bombRange = { Vec2(mP.x - 40 * bombPower,mP.y),Vec2(mP.x + 40 * bombPower,mP.y),Vec2(mP.x,mP.y + 40 * bombPower),Vec2(mP.x,mP.y - 40 * bombPower) };
	myBomb->initExplode(bombRange);

}

bool gamelayer::moveifPlayer(int doerTag) {

	for (auto figures : players) //遍历所有玩家
	{
		if (figures != players[doerTag]) //与其他玩家进行碰撞检测
		{
			Point figP = figures->position;
			Point doP = players[doerTag]->position;
			if (fabsf(figP.x - doP.x) <= 5 && fabsf(figP.y - doP.y) <= 5) //碰撞
			{
				if (figures->team != players[doerTag]->team) //是敌队
				{
					if (figures->state == STATE_BOXED) //敌队已被困
					{
						figures->Die(0.0);
						++players[doerTag]->killNum;
						return true;
					}
					if (figures->state == STATE_FREE&&figures->speed != players[doerTag]->speed) //敌队活着，不能一起走
					{
						return figures->direction == players[doerTag]->direction ? false : true;
					}
				}
				else {//战友
					if (figures->state == STATE_BOXED)//救战友
					{
						figures->BeSaved();
						return true;
					}
					if (figures->state == STATE_FREE&&figures->speed != players[doerTag]->speed) //友队活着，不能一起走
					{
						return figures->direction == players[doerTag]->direction ? false : true;
					}
				}
			}
		}
	}
	return true;
}

void gamelayer::bombifPlayer(std::vector<Point>&vec) {
	for (auto figures : players) {
		Point mP = figures->position;
		if (((mP.x < vec[1].x + 20) && (mP.x > vec[0].x - 20) && (mP.y < vec[1].y + 20) && (mP.y > vec[1].y - 20)) || ((mP.x < vec[2].x + 20) && (mP.x > vec[2].x - 20) && (mP.y < vec[2].y + 20) && (mP.y > vec[3].y - 20))) {
			figures->BeBoxed();
		}
	}
}