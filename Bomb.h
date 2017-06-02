#ifndef _BOMB_H_INCLUDED
#define _BOMB_H_INCLUDED

#include "cocos2d.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "gamelayer.h"
class gamelayer;
USING_NS_CC;

#define explode_end_left 1
#define explode_end_right 2
#define explode_end_up 3
#define explode_end_down 4
#define explode_line_left 5
#define explode_line_right 6
#define explode_row_up 7
#define explode_row_down 8

class Bomb:	public Layer
{
public:
	Bomb();
	~Bomb();
	Sprite* bomb;
	Point position;
	std::vector<Sprite*> explosionSprite;
	std::vector<Point> bombRange;
	gamelayer* myGamelayer;

	virtual bool init();
	CREATE_FUNC(Bomb);
	static Bomb* createBombSprite(Point position);
	Animate* createAnimate(const char *action, int num,int time);
	void bombDynamic();
	void bombExplode(float dt);
	void deleteBomb();
	void explode(float dt);
	void addChildExplosion(float beg, float end, float remain,int tag);
	void addExplosionAnimate(Point aniPosition, int tag);
	void deleteExplode(float dt);
	void initExplode(std::vector<Point>&vec);//vec[0]�Ǻ�������࣬vec[1]�Ǻ������ң�vec[2]�������ϣ�vec[3]��������
};

#endif // !_BOMB_H_INCLUDED