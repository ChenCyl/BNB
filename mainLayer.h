#pragma once
#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;
class mainLayer:public Layer
{
public:
	mainLayer();
	~mainLayer();

	void change(Object* pSender, Control::EventType event);
	CREATE_FUNC(mainLayer);
	virtual bool init();
	void addSwitch();
	void stopMusic();
};

