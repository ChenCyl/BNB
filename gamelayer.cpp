#include "gamelayer.h"
#include "SimpleAudioEngine.h"
#include "Player_one.h"
#include "Player_se.h"
#include "TiledMap.h"
#include "cocos2d.h"
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

	Sprite* gameFrame = Sprite::create("BG.png");
	gameFrame->setAnchorPoint(ccp(0, 0));
	addChild(gameFrame);

	return true;
};

void gamelayer::gamelayerInit() {

	loadMap();
	loadFigure();
	loadBar();

	schedule(schedule_selector(gamelayer::myUpdate), 0.2f);
}

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
	myMap = TiledMap::createTiledMap();
	myMap->_map->setPosition(-20, 0);
	myMap->_map->setAnchorPoint(ccp(0, 0));
	addChild(myMap, 1);
}

void gamelayer::loadFigure() {
	Size winSize = Director::getInstance()->getWinSize();
	Point mapSize = Vec2(winSize.width *0.34, winSize.height*0.5);
	int figureNum = 0;
	for (int i = 0;i < playerOne;i++) {
		Player_one* player1 = Player_one::createFigureSprite(Vec2(myMap->_figureOriginX, myMap->_figureOriginY), DOWN, USER, figureTeam[figureNum+i], 0);
		player1->myGamelayer = this;
		players.push_back(player1);
		myMap->_map->addChild(player1, 2);
		figureNum++;
	}

	for (int i = 0;i < playerSe;i++) {
		Player_se* player2 = Player_se::createFigureSprite(Vec2(mapSize.x / 2 - 25,
			mapSize.y / 2 + 50), DOWN, USER, figureTeam[figureNum+i], 1);
		player2->myGamelayer = this;
		players.push_back(player2);
		myMap->_map->addChild(player2, 2);
	}

	for (auto& figure : players) {
		switch (figure->team) {
		case RED:
			red.push_back(figure);
			break;
		case GREEN:
			green.push_back(figure);
			break;
		case BLUE:
			blue.push_back(figure);
			break;
		case YELLOW:
			yellow.push_back(figure);
			break;
		default:
			break;
		}

		switch (figure->type)
		{
		case USER:
			user.push_back(figure);
			break;
		case COMPUTER:
			ai.push_back(figure);
			break;
		default:
			break;
		}
	}

}

void gamelayer::loadBar() {
	CountDownBar = countDownBar::createCountBar(FULL_TIME);
	addChild(CountDownBar);
}

void gamelayer::figureMove(int tag, int direction) {
	bool canMove = !myMap->isCollision(players[tag]->position,direction);
	players[tag]->Move(direction, (canMove&&moveifPlayer(tag)));
	getTool(tag, players[tag]->position);
}

void gamelayer::putBomb(int playerTag, Point position) {
	Point mP = players[playerTag]->position;//转换坐标
	mP = myMap->tileCoordFromPosition(mP);
	mP = myMap->PositionFromTileCoord(mP);
	int bombPower = players[playerTag]->bombPower;
	auto myBomb = Bomb::createBombSprite(mP);
	myBomb->myGamelayer = this;
	myBomb->bombPower = bombPower;
	myMap->_map->addChild(myBomb, 0);
	myBomb->bombDynamic();
	std::vector<Point> bombRange = myMap->calculateBomRangPoint(mP, bombPower);
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

void gamelayer::getTool(int tag, Point position){
	int toolType = myMap->eatTool(position);
	if (toolType != 0) {
		players[tag]->CollectTool(toolType);
	}
}


void gamelayer::myUpdate(float dt) {

	bool greenAllDie = true;
	bool redAllDie = true;
	bool blueAllDie = true;
	bool yellowAllDie = true;
	bool aiAllDie = true;
	bool userAllDie = true;
	//获得每队现状态 ai与玩家的状态
	for (auto& figure : players) {
		switch (figure->team)
		{
		case GREEN:
			greenAllDie = greenAllDie && (figure->state == STATE_DIED);
			break;
		case RED:
			redAllDie = redAllDie && (figure->state == STATE_DIED);
			break;
		case BLUE:
			blueAllDie = blueAllDie && (figure->state == STATE_DIED);
			break;
		case YELLOW:
			yellowAllDie = yellowAllDie && (figure->state == STATE_DIED);
			break;
		default:
			break;
		}

		switch (figure->type)
		{
		case USER:
			userAllDie = userAllDie&&figure->state == STATE_DIED;
			break;
		case COMPUTER:
			aiAllDie = aiAllDie&&figure->state == STATE_DIED;
			break;
		default:
			break;
		}
	}

	//时间到了,游戏结束
	if (timeLeft <= 0) {
		unschedule(schedule_selector(gamelayer::myUpdate));
		if (isClient) {
			//客户端版：时间结束时，玩家没死算赢
			for (auto& figure : players) {
				if (figure->type == USER) {
					figure->Win();
					winPlayers.push_back(figure);
				}
			}
		}
		else {
			//联网版：四组都有人活着或者四组都同时死去，则为平局；其他情况，有活着人物的队伍胜利，全死亡的队伍失败
			if (greenAllDie + redAllDie + blueAllDie + yellowAllDie != 4 && greenAllDie + redAllDie + blueAllDie + yellowAllDie != 0) {
				if (!greenAllDie) {
					for (auto& figure : green) {
						figure->Win();
						winPlayers.push_back(figure);
					}
				}
				if (!redAllDie) {
					for (auto& figure : red) {
						figure->Win();
						winPlayers.push_back(figure);
					}
				}
				if (!blueAllDie) {
					for (auto& figure : blue) {
						figure->Win();
						winPlayers.push_back(figure);
					}
				}
				if (!yellowAllDie) {
					for (auto& figure : yellow) {
						figure->Win();
						winPlayers.push_back(figure);
					}
				}
			}
		}
		/*scheduleOnce(schedule_selector(), 1.0f);*/  //展示得分的函数
		return;
	}

	//时间未到，但有人赢了
	if (timeLeft > 0) {
		timeLeft -= dt;
		CountDownBar->barUpdate(timeLeft, FULL_TIME);
		//客户端版：
		if (isClient) {
			////做出来ai的情况下：ai全死或者玩家全死游戏结束
			//if (aiAllDie + userAllDie == 1) {
			//	unschedule(schedule_selector(gamelayer::myUpdate));
			//	if (aiAllDie) {
			//		for (auto& figure:user) {
			//			figure->Win();
			//			winPlayers.push_back(figure);
			//		}
			//	}
			//	else {
			//		for (auto& figure : ai) {
			//			figure->Win();
			//			winPlayers.push_back(figure);
			//		}
			//	}
			//}
			///*scheduleOnce(schedule_selector(), 1.0f);*/  //展示得分的函数
			//return;

			//暂时做成没有ai的：只剩一组队伍则胜利
			if (greenAllDie + redAllDie + blueAllDie + yellowAllDie == 3) {
				unschedule(schedule_selector(gamelayer::myUpdate));
				if (!greenAllDie) {
					for (auto& figure : green) {
						figure->Win();
						winPlayers.push_back(figure);
					}
				}
				if (!redAllDie) {
					for (auto& figure : red) {
						figure->Win();
						winPlayers.push_back(figure);
					}
				}
				if (!blueAllDie) {
					for (auto& figure : blue) {
						figure->Win();
						winPlayers.push_back(figure);
					}
				}
				if (!yellowAllDie) {
					for (auto& figure : yellow) {
						figure->Win();
						winPlayers.push_back(figure);
					}
				}
				/*scheduleOnce(schedule_selector(), 1.0f);*/  //展示得分的函数
				return;
			}
		}
		//联机版：
		if (!isClient) {//仅剩一组没死光算胜利
			if (greenAllDie + redAllDie + blueAllDie + yellowAllDie == 3) {
				unschedule(schedule_selector(gamelayer::myUpdate));
				if (!greenAllDie) {
					for (auto& figure : green) {
						figure->Win();
						winPlayers.push_back(figure);
					}
				}
				if (!redAllDie) {
					for (auto& figure : red) {
						figure->Win();
						winPlayers.push_back(figure);
					}
				}
				if (!blueAllDie) {
					for (auto& figure : blue) {
						figure->Win();
						winPlayers.push_back(figure);
					}
				}
				if (!yellowAllDie) {
					for (auto& figure : yellow) {
						figure->Win();
						winPlayers.push_back(figure);
					}
				}
				/*scheduleOnce(schedule_selector(), 1.0f);*/  //展示得分的函数
				return;
			}
		}
	}

}