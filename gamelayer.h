#pragma once
#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
#include "Figure.h"
#include "Bomb.h"
USING_NS_CC;
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4

#define MAP1 1
#define MAP2 2
#define MAP3 3
#define MAP4 4
class Figure;
class gamelayer :public Layer
{
public:
	CREATE_FUNC(gamelayer);
	virtual bool init();
	void menucallback(Ref *psender);

public:
	SceneManager *tsm;

	int playerOne = 1;
	int playerSe = 1;
	int playerAi = 0;
	//	TMXTiledMap* map;//实际上应该是一个map类的对象;
	//	list<Tool*> toolManager;管理所有的道具;
	std::vector<Figure*> players;

public:
	void loadFigure();
	void loadMap();
	//人物移动：
	void figureMove(int tag, int direction);
	//碰撞检测：
	/*int ifTool(int doerTag);*/
	bool moveifPlayer(int doerTag);
	void bombifPlayer(std::vector<Point>&vec);

	//放置炸弹：
	void putBomb(int playerTag, Point position);

};
