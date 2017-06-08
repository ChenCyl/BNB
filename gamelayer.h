#pragma once
#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
#include "Figure.h"
#include "Bomb.h"
#include "TiledMap.h"
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
	void gamelayerInit();

public:
	SceneManager *tsm;
	std::map<int, int> figureTeam;
	int playerOne = 1;
	int playerSe = 0;
	int playerAi = 0;
	TiledMap* myMap;
	//	TMXTiledMap* map;//ʵ����Ӧ����һ��map��Ķ���;
	//	list<Tool*> toolManager;�������еĵ���;
	std::vector<Figure*> players;

public:
	void loadFigure();
	void loadMap();
	//�����ƶ���
	void figureMove(int tag, int direction);
	//��ײ��⣺
	/*int ifTool(int doerTag);*/
	bool moveifPlayer(int doerTag);
	void bombifPlayer(std::vector<Point>&vec);

	//����ը����
	void putBomb(int playerTag, Point position);
	/*void showTool(float dt);*/

};
