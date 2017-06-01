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
	int user;
	int map;
	CREATE_FUNC(chooselayer);
	virtual bool init();
	void menucallback(Ref *psender);
	void figurecallback(Ref *psender);
	void mapcallback(Ref *psender);
public:
	SceneManager *tsm;
	
};