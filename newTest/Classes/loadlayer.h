#pragma once
#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
#include "mainLayer.h"
USING_NS_CC;
class loadlayer :public mainLayer
{
public:
	CREATE_FUNC(loadlayer);
	virtual bool init();
	void menucallback(Ref *psender);
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

public:
	SceneManager *tsm;
};