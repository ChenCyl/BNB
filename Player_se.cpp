#include "Player_se.h"



Player_se::Player_se()
{

}


Player_se::~Player_se()
{
}

Player_se* Player_se::createFigureSprite(Point position, int direction, int type, int team,int tag) {
	Player_se* figure = new Player_se();
	if (figure&&figure->init()) {
		figure->autorelease();
		figure->figureInit(position, direction, type, team,tag);
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
	
	schedule(schedule_selector(Player_se::update), 0.2f);
	return true;
}
void Player_se::update(float dt) {
	Node::update(dt);
	if (state == STATE_FREE) {
		EventKeyboard::KeyCode delegateKey = isKeyPressed();
		switch (delegateKey) {
		case EventKeyboard::KeyCode::KEY_A:
			myHelloworld->figureMove(tag, LEFT);
			break;
		case EventKeyboard::KeyCode::KEY_D:
			myHelloworld->figureMove(tag, RIGHT);
			break;
		case EventKeyboard::KeyCode::KEY_W:
			myHelloworld->figureMove(tag, UP);
			break;
		case EventKeyboard::KeyCode::KEY_S:
			myHelloworld->figureMove(tag, DOWN);
			break;
		case EventKeyboard::KeyCode::KEY_F:
			if (bombNum_avail > 0) {
				--bombNum_avail;
				myHelloworld->putBomb(tag, position);
				scheduleOnce(schedule_selector(Player_se::recoverBomb), 4.4f);
			};
			break;
		default:
			DoStand();
			break;
		}
	}
}

EventKeyboard::KeyCode Player_se::isKeyPressed() {
	auto map_it = keys.cbegin();
	while (map_it != keys.cend()) {
		if (map_it->second == 1) {
			if (map_it->first == EventKeyboard::KeyCode::KEY_A || map_it->first == EventKeyboard::KeyCode::KEY_D || map_it->first == EventKeyboard::KeyCode::KEY_W || map_it->first == EventKeyboard::KeyCode::KEY_S || map_it->first == EventKeyboard::KeyCode::KEY_F)
			{
				return map_it->first;
			}
		}
		map_it++;
	}
	return EventKeyboard::KeyCode::KEY_0;
}