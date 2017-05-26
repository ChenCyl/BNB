#pragma once
#include <iostream>
#include <cocos2d.h>
#include "SceneManager.h"
using namespace std;
class loadlayer :public Layer
{
public:
	CREATE_FUNC(loadlayer);
	virtual bool init();

public:
	SceneManager *tsm;
};