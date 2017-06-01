#pragma once
#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
USING_NS_CC;
class serverlayer :public Layer
{
public:
	CREATE_FUNC(serverlayer);
	virtual bool init();
	void menucallback(Ref *psender);

public:
	SceneManager *tsm;
};