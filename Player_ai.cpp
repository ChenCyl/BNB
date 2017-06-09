#include "Player_ai.h"



Player_ai::Player_ai()
{
}


Player_ai::~Player_ai()
{
}


bool Player_ai::init() {
	if (!Layer::init()) {
		return false;
	}
	schedule(schedule_selector(Player_ai::update), 0.1f);
	return true;
}

Player_ai* Player_ai::createFigureSprite(Point position, int direction, int type, int team, int tag) {
	Player_ai* figure = new Player_ai();

	if (figure&&figure->init()) {
		figure->autorelease();
		figure->figureInit(position, direction, type, team, tag);
		return figure;
	}
	CC_SAFE_DELETE(figure);

	return NULL;
}


void Player_ai::update(float dt) {

	//可以调用myGamelayer内的函数来获得所在位置附近的信息
	


}
