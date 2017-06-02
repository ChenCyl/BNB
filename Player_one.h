#ifndef _PLAYER_ONE_H_INCLUDED
#define _PLAYER_ONE_H_INCLUDED
#include<cocos2d.h>
#include"Figure.h"
USING_NS_CC;
class Player_one:public Figure
{
public:
	Player_one();
	~Player_one();

	std::map<EventKeyboard::KeyCode, bool> keys;

	EventKeyboard::KeyCode isKeyPressed();
	void update(float dt) override;
	virtual bool init();
	CREATE_FUNC(Player_one);
	static Player_one* createFigureSprite(Point position, int direction, int type, int team,int tag);
};
#endif
