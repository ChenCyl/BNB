#pragma once
#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
using namespace std;
class finishlayer :public Layer
{
public:
	CREATE_FUNC(finishlayer);
	virtual bool init();

public:
	ScenemManager *tsm;
};

