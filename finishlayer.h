#pragma once
#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
USING_NS_CC;
class finishlayer :public Layer
{
public:
	CREATE_FUNC(finishlayer);
	virtual bool init();
	void menucallback(Ref *psender);

public:
	SceneManager *tsm;
};

