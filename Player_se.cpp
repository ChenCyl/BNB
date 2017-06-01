#include "Player_se.h"



Player_se::Player_se()
{

}


Player_se::~Player_se()
{
}

Player_se* Player_se::createFigureSprite(Point position, int direction, int type, int team) {
	Player_se* figure = new Player_se();
	if (figure&&figure->init()) {
		figure->autorelease();
		figure->figureInit(position, direction, type, team);
		return figure;
	}
	CC_SAFE_DELETE(figure);
	return NULL;
}
bool Player_se::init() {
	if (!Layer::init()) {
		return false;
	}

	auto myKeyListener = EventListenerKeyboard::create();
	myKeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = true;
	};
	myKeyListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);
	Move(LEFT, true);
	schedule(schedule_selector(Player_se::update), 0.2f);
	return true;
}
void Player_se::update(float dt) {
	Node::update(dt);
	auto leftArrow = EventKeyboard::KeyCode::KEY_A;
	auto rightArrow = EventKeyboard::KeyCode::KEY_D;
	if (state == STATE_FREE) {
		if (isKeyPressed(leftArrow)) {
			Move(LEFT, true);CCLOG("print A");
		}
		else {
			if (isKeyPressed(rightArrow)) {
				Move(RIGHT, true);
			}
			else {
				DoStand();
			}
		}
	}
}
bool  Player_se::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	return keys[keyCode] == 1 ? 1 : 0;
}