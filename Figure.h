#ifndef _FIGURE_H_INCLUDED
#define _FIGURE_H_INCLUDED
#include "cocos2d.h"
#include "Bomb.h"
#include "gamelayer.h"
class gamelayer;
#define NO_DIRECTION 0		//玩家动作方向
#define LEFT 1			
#define RIGHT 2
#define UP 3
#define DOWN 4

#define USER 1			//人物身份
#define COMPUTER 2

#define RED 1			//人物队属
#define GREEN 2
#define BLUE 3
#define YELLOW 4

#define STATE_FREE 0	//人物状态
#define STATE_BOXED 1
#define STATE_DIED 2

#define TOOL_SHOE 1		//道具种类
#define TOOL_BOMB 2
#define TOOL_LIQUID 3
#define TOOL_COIN 4
#define TOOL_STRAW 5
#define TOOL_BANANA 6

USING_NS_CC;
//人物
class Figure:public Layer
{
public:
	Figure();
	~Figure();
	int type;//人物类型
	int team;//队伍
	int direction;//人物方向有4种
	Point position;//人物坐标
	Sprite* sprite;//显示人物
	int tag;//人物是gamelayer层内的players[tag]
	Sprite* Portrait;
	bool win=false;

	float speed=10;//速度
	int killNum=0;//杀敌数
	int saveNum=0;//救人数
	int state=STATE_FREE;//状态
	int score=0;//分数
	int bombNum=1;//炸弹个数
	int bombNum_avail=1;//剩余炸弹个数
	int bombPower=1;//炸弹威力
	gamelayer* myGamelayer;//所在的游戏层
	LabelTTF* labelScore;
	LabelTTF* labelBombNum_avail;
	LabelTTF* labelKill;
	LabelTTF* labelSave;
	LabelTTF* labelTag;
	
	static Figure* createFigureSprite(Point position, int direction,int type, int team,int tag);//创建人物
	void figureInit(Point position, int direction, int type, int team,int tag);//初始化人物
	Animate* createAnimate(int direction, int team, const char*action, int num,int time);//创建动画

	void Move(int myDirection, bool i);
	void DoStand();
	void CollectTool(unsigned int i);
	void BeBoxed();
	void BeSaved();
	void Die(float dt);
	void Win();
	void Delete();

	void labelInit(int tag);
	void updateLabel();
	void stopAllSchedules();
	void gameover();

	virtual bool init();
	CREATE_FUNC(Figure);
};
#endif // !_FIGURE_H_INCLUDED
