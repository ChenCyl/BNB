#pragma once
#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
#include "Figure.h"
#include "Bomb.h"
#include "TiledMap.h"
#include "countDownBar.h"

USING_NS_CC;
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4

#define MAP1 1
#define MAP2 2
#define MAP3 3
#define MAP4 4

#define FULL_TIME 180.0
class Figure;
class countDownBar;
class TiledMap;
class gamelayer :public Layer
{
public:
	CREATE_FUNC(gamelayer);
	virtual bool init();
	void menucallback(Ref *psender);
	void gamelayerInit();

public:
	int playerOne = 1;
	int playerSe = 0;
	int playerAi = 0;
	float timeLeft = FULL_TIME;
	bool isClient;

	TiledMap* myMap;
	countDownBar* CountDownBar;
	SceneManager *tsm;

	std::map<int, int> figureTeam = { { 0,RED },{ 1,BLUE } };
	std::vector<Figure*> players;
	std::vector<Figure*> winPlayers;
	std::vector<Figure*> red;
	std::vector<Figure*> green;
	std::vector<Figure*> blue;
	std::vector<Figure*> yellow;
	std::vector<Figure*> user;
	std::vector<Figure*> ai;

public:
	void loadFigure();
	void loadMap();
	void loadBar();
	//人物移动：
	void figureMove(int tag, int direction);
	//碰撞检测：
	
	bool moveifPlayer(int doerTag);
	void bombifPlayer(std::vector<Point>&vec);

	//放置炸弹：
	void putBomb(int playerTag, Point position);
	
	void getTool(int tag, Point position);

	//实时更新：
	void myUpdate(float dt);

};
