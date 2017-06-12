#ifndef _BOMB_H_INCLUDED
#define _BOMB_H_INCLUDED

#include "cocos2d.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "gamelayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
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
	int bombPower;
	int playerTag;
	int bombTag;
	bool exit=true;

	virtual bool init();
	CREATE_FUNC(Bomb);
	static Bomb* createBombSprite(Point& position,int& playerTag,int& bombPower,int& bombTag,gamelayer* gameLayer);
	Animate* createAnimate(const char *action, int num,int time);
	void bombDynamic();
	void bombExplode(float dt);
	void deleteBomb();
	void explode(float dt);
	void addChildExplosion(float beg, float end, float remain,int tag);
	void addExplosionAnimate(Point aniPosition, int tag);
	void deleteExplode(float dt);
	void initExplode(std::vector<Point>&vec);//vec[0]是横排最左侧，vec[1]是横排最右，vec[2]竖排最上，vec[3]竖排最下
	void showTool(float dt);
};

#endif // !_BOMB_H_INCLUDED