#ifndef _PLAYER_AI_H_INCLUDED_
#define _PLAYER_AI_H_INCLUDED_
#include "cocos2d.h"
#include "Figure.h"
USING_NS_CC;
class Player_ai:	public Figure
{
public:
	Player_ai();
	~Player_ai();

	void update(float dt) override;//������дai���㷨
	virtual bool init();
	CREATE_FUNC(Player_ai);
	static Player_ai* createFigureSprite(Point position, int direction, int type, int team, int tag);
};
#endif
