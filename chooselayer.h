#pragma once
#include <iostream>
#include <cocos2d.h>
#include "SceneManager.h"
using namespace std;
class chooselayer :public Layer
{
public:
	CREATE_FUNC(chooselayer);
	virtual bool init();
public:
	SceneManager *tsm;
};