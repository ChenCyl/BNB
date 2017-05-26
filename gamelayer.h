#pragma once
#include <iostream>
#include <cocos2d.h>
#include "SceneManger.h"
using namespace std;
class gamelayer :public Layer
{
public:
	CREATE_FUNC(gamelayer);
	virtual bool init();
public:
	SceneManager *tsm;
};
