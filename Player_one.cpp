#include "Player_one.h"



Player_one::Player_one()
{
	
}


Player_one::~Player_one()
{
}

Player_one* Player_one::createFigureSprite(Point position, int direction, int type, int team,int tag) {
	Player_one* figure = new Player_one();
	if (figure&&figure->init()) {
		figure->autorelease();
		figure->figureInit(position, direction, type, team,tag);
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
	if (state == STATE_FREE) {
		EventKeyboard::KeyCode delegateKey = isKeyPressed();
		switch (delegateKey) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			myHelloworld->figureMove(tag, LEFT);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			myHelloworld->figureMove(tag, RIGHT);
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			myHelloworld->figureMove(tag, UP);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			myHelloworld->figureMove(tag, DOWN);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
				if (bombNum_avail > 0) {
					--bombNum_avail;
					myHelloworld->putBomb(tag, position);
					scheduleOnce(schedule_selector(Player_one::recoverBomb), 4.4f);
				}
				break;
		default:
			DoStand();
			break;
		}
	}
}

EventKeyboard::KeyCode Player_one::isKeyPressed() {
	auto map_it = keys.cbegin();
	while (map_it != keys.cend()) {
		if (map_it->second == 1) {
			if (map_it->first == EventKeyboard::KeyCode::KEY_LEFT_ARROW || map_it->first == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || map_it->first == EventKeyboard::KeyCode::KEY_UP_ARROW || map_it->first == EventKeyboard::KeyCode::KEY_DOWN_ARROW || map_it->first == EventKeyboard::KeyCode::KEY_SPACE)
			{
				return map_it->first;
			}
		}
		map_it++;
	}
	return EventKeyboard::KeyCode::KEY_0;
}