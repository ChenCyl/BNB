#ifndef _COUNTDOWNBAR_H_INCLUDED_
#define _COUNTDOWNBAR_H_INCLUDED_
#include "cocos2d.h"
USING_NS_CC;
class countDownBar:public Layer
{
public:
	countDownBar();
	~countDownBar();
	Sprite* barBG;
	Sprite* CountDownBar;
	float timeFull;
	float timeNow;
	LabelTTF* label;

	void barUpdate(float timeNow,float timeFull);
	static countDownBar* createCountBar(float timeFull);
	virtual bool init();
	CREATE_FUNC(countDownBar);

};

#endif;
