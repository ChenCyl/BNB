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

#define BombOther 1
#define BombJust 2
#define WaitBomb 3
class Figure;
class countDownBar;
class TiledMap;
class Bomb;
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
	int allBombNum = 0;
	float timeLeft = FULL_TIME;
	bool isClient;
	TiledMap* myMap;

	countDownBar* CountDownBar;
	SceneManager *tsm;

	std::map<int, int> figureTeam = { { 0,RED },{ 1,BLUE } };
	std::list<Bomb*> allBombs;
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
	void teamInitForAi(int figureNum);
	//人物移动：
	void figureMove(int tag, int direction);
	//碰撞检测：
	bool moveifBomb(int tag,int direction);//有炮弹障碍，返回true;
	bool moveifPlayer(int doerTag);//移动时遇到玩家，若所遇是被困敌人，就执行kill；所遇是被困队友，就执行save；
	void bombifPlayer(std::vector<Point>&vec);//检测炸弹是否炸到了人物
	int bombifBomb(std::vector<Point>&vec,int& bombTag);//检测炸弹是否需要引炸别的炸弹
	void bombBomb(std::vector<Point>&vec,  int& bombTag);//引爆炸弹
	//放置炸弹：
	void putBomb(int playerTag, Point position);
	bool canBomb(Point mP);
	
	//有道具就捡道具，没道具就算了：
	void getTool(int tag, Point position);

	//实时更新，检测游戏是否结束：
	void myUpdate(float dt);

	//简单地写了一个gameover的函数，分数榜待完善
	void gameOver(float dt);

	void finishGame(float dt);
};
