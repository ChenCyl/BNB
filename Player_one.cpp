#include "Player_one.h"



Player_one::Player_one()
{
	
}


Player_one::~Player_one()
{
}

Player_one* Player_one::createFigureSprite(Point position, int direction, int type, int team) {
	Player_one* figure = new Player_one();
	if (figure&&figure->init()) {
		figure->autorelease();
		figure->figureInit(position, direction, type, team);
		return figure;
	}
	CC_SAFE_DELETE(figure);
	return NULL;
}
bool Player_one::init() {
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

	schedule(schedule_selector(Player_one::update), 0.2f);
	return true;
}
void Player_one::update(float dt) {
	Node::update(dt);
	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	auto rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	auto upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW;
	auto downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	if (state == STATE_FREE) {
		if (isKeyPressed(leftArrow)) {
			Move(LEFT, true);
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
bool  Player_one::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	return keys[keyCode] == 1 ? 1 : 0;
}