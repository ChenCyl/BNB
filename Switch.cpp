#include "Switch.h"
#include "SimpleAudioEngine.h"

Switch* Switch::createSwitch(int sceneType, int gameType, bool isGamelayer)
{
	Switch* mySwitch = new Switch();
	if (mySwitch&&mySwitch->init()) {
		mySwitch->autorelease();
		mySwitch->switchInit(sceneType, gameType, isGamelayer);
		return mySwitch;
	}
	CC_SAFE_DELETE(mySwitch);
	return NULL;
}

bool Switch::init() {
	if (!Layer::init()) {
		return false;
	}
	
	return true;
}

void Switch::switchInit(int msceneType, int mgameType, bool misGamelayer) {
	sceneType = msceneType;
	gameType = mgameType;
	isGamelayer = misGamelayer;

	if (!isGamelayer) {
		for (int i = 1;i < 3;++i) {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(String::createWithFormat("bg%d.mp3", i)->getCString());
		}
	}
	else {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(String::createWithFormat("bg%d.mp3", gameType)->getCString());
		for (int i = 1;i < 10;++i) {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(String::createWithFormat("effect%d.wav", i)->getCString());
		}
	}
	auto* switchBG = Sprite::create("background.png");
	auto* switchOn = Sprite::create("on.png");
	auto* switchOff = Sprite::create("off.png");
	auto* switchBar = Sprite::create("button.png");
	auto* on = Label::create("on", "Arial", 15);
	auto* off = Label::create("pause", "Arial", 15);
	auto* controlSwitch = ControlSwitch::create(switchBG, switchOn, switchOff, switchBar, on, off);
	controlSwitch->setPosition(Vec2(80, 40));
	addChild(controlSwitch);
	controlSwitch->addTargetWithActionForControlEvents(this, cccontrol_selector(Switch::change), Control::EventType::VALUE_CHANGED);
}

void Switch::change(Object* pSender,Control::EventType event) {
	if (event == Control::EventType::VALUE_CHANGED) {
		auto* s = (ControlSwitch*)pSender;
		if (s->isOn()) {
			if (isGamelayer) {
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(String::createWithFormat("bg%d.mp3", gameType)->getCString(), true);
			}
			else {
				sceneType % 2 == 0 ? CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg1.mp3", true) : CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg2.mp3", true);
			}
		}
		else {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		}
	}
}