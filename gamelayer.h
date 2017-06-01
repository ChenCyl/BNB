#pragma once
#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
USING_NS_CC;
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4

#define MAP1 1
#define MAP2 2
#define MAP3 3
#define MAP4 4

class gamelayer :public Layer
{
public:
	CREATE_FUNC(gamelayer);
	virtual bool init();
	void menucallback(Ref *psender);
public:
	SceneManager *tsm;
};
