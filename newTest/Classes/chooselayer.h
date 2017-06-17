#pragma once
#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"

#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4

#define MAP1 1
#define MAP2 2
#define MAP3 3
#define MAP4 4

class chooselayer :public Layer
{
public:
	int userOne=GREEN,userTwo=GREEN;
	int map=MAP1;
	int chooseNum;
	bool isClient;

	cocos2d::Sprite* _firmFigure;
	cocos2d::Sprite* _firmFigure2p;
	cocos2d::Sprite* _firmMap;
	std::vector<Texture2D*> _chooseFigure;
	std::vector<Texture2D*> _chooseFigure2p;
	std::vector<Texture2D*> _chooseMap;

	CREATE_FUNC(chooselayer);
	virtual bool init();
	void menucallback(Ref *psender);
	void figurecallback(Ref *psender);
	void mapcallback(Ref *psender);
	void showFigureChoose(cocos2d::Point pos, float tag = 100);
	void chooselayerInit();
	void showMapChoose(cocos2d::Point pos);
public:
	SceneManager *tsm;
	
};