#include "mainLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;


mainLayer::mainLayer()
{
}


mainLayer::~mainLayer()
{
}


bool mainLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	return true;
}

void mainLayer::change(Object* pSender, Control::EventType event) {
	if (event == Control::EventType::VALUE_CHANGED) {
		auto* s = (ControlSwitch*)pSender;
		if (s->isOn()) {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}
		else {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		}
	}
}

void mainLayer::addSwitch() {
	auto* switchBG = Sprite::create("background.png");
	auto* switchOn = Sprite::create("on.png");
	auto* switchOff = Sprite::create("off.png");
	auto* switchBar = Sprite::create("button.png");
	auto* on = Label::create("on", "Arial", 15);
	auto* off = Label::create("pause", "Arial", 15);
	auto* controlSwitch = ControlSwitch::create(switchBG, switchOn, switchOff, switchBar, on, off);
	controlSwitch->setPosition(Vec2(80, 40));
	addChild(controlSwitch);
	controlSwitch->addTargetWithActionForControlEvents(this, cccontrol_selector(mainLayer::change), Control::EventType::VALUE_CHANGED);

}

void mainLayer::stopMusic() {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}