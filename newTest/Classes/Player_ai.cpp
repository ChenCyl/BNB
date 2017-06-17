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
	schedule(schedule_selector(Player_ai::update), 0.2f);
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
	bool canUp = myGamelayer->ifMove(tag, UP);
	bool isDangerUp = myGamelayer->ifDanger(Vec2(position.x, position.y + speed));
	bool canRight = myGamelayer->ifMove(tag, RIGHT);
	bool isDangerRight = myGamelayer->ifDanger(Vec2(position.x + speed, position.y));
	bool canDown = myGamelayer->ifMove(tag, DOWN);
	bool isDangerDown = myGamelayer->ifDanger(Vec2(position.x, position.y - speed));
	bool canLeft = myGamelayer->ifMove(tag, LEFT);
	bool isDangerLeft = myGamelayer->ifDanger(Vec2(position.x - speed, position.y));
	if (state == STATE_FREE) {
		if (canUp && !isDangerUp) {
			myGamelayer->figureMove(tag, UP);
		
		}
		else {
			if (canRight && !isDangerRight) {
				myGamelayer->figureMove(tag, RIGHT);
			
			}
			else {
				if (canDown && !isDangerDown) {
					myGamelayer->figureMove(tag, DOWN);
					
				}
				else {
					if (canLeft && !isDangerLeft) {
						myGamelayer->figureMove(tag, LEFT);
						
					}
				}
			}
		}
	}
}