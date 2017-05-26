#ifndef _BOMB_H_INCLUDED
#define _BOMB_H_INCLUDED

#include "cocos2d.h"
#include <vector>
USING_NS_CC;

#define explode_end_left 1
#define explode_end_right 2
#define explode_end_up 3
#define explode_end_down 4
#define explode_line 5
#define explode_row 6

class Bomb:	public Sprite
{
public:
	Bomb();
	~Bomb();
	int bombNum;//炸弹个数
	int bombNum_avail;//剩余炸弹个数
	int bombPower;//炸弹威力
	Point position;

	static Bomb* create(const char* FileName);
	void bombDynamic();
	void bombExplode();
	void explode(std::vector<Point> &vec_positions, std::vector<int> &vec_types);
};

#endif // !_BOMB_H_INCLUDED
