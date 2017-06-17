#ifndef _PLAYER_SE_H_INCLUDED
#define _PLAYER_SE_H_INCLUDED
#include<cocos2d.h>
#include"Figure.h"
USING_NS_CC;
class Player_se :public Figure
{
public:
	Player_se();
	~Player_se();

	std::map<EventKeyboard::KeyCode, bool> keys;

	EventKeyboard::KeyCode isKeyPressed();
	void update(float dt) override;
	virtual bool init();
	CREATE_FUNC(Player_se);
	static Player_se* createFigureSprite(Point position, int direction, int type, int team,int tag);
};
#endif
