#include "countDownBar.h"
USING_NS_CC;


countDownBar::countDownBar()
{
}


countDownBar::~countDownBar()
{
}

void countDownBar::barUpdate(float timeNow, float timeFull) {
	auto* timeString=String::createWithFormat("%d:%d", (int)timeNow/60,(int)timeNow%60)->getCString();
	label->setString(timeString);
	
	CountDownBar->setScaleX(timeNow / timeFull);
}

countDownBar* countDownBar::createCountBar(float timeFull) {
	countDownBar* bar = new countDownBar();
	bar->timeFull = timeFull;
	if (bar&&bar->init()) {
		bar->autorelease();
		return bar;
	}
	CC_SAFE_DELETE(bar);
	return NULL;
}
bool countDownBar::init() {
	if (!Layer::init()) {
		return false;
	}
	barBG = Sprite::create("barBG.png");
	barBG->setAnchorPoint(Vec2(0, 1));
	barBG->setScaleX(6);
	barBG->setPosition(Vec2(148,597));
	addChild(barBG);
	CountDownBar = Sprite::create("bar.png");
	CountDownBar->setAnchorPoint(Vec2(0, 0));
	CountDownBar->setPosition(0, 0);
	barBG->addChild(CountDownBar);
	label = LabelTTF::create("03:00", "Arial", 25);
	label->setAnchorPoint(Vec2(0, 1));
	label->setFontFillColor(Color3B(240, 248, 255));
	
	label->setPosition(Vec2(650, 597));
	addChild(label);
	return true;
}

