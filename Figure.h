#ifndef _FIGURE_H_INCLUDED
#define _FIGURE_H_INCLUDED
#include "cocos2d.h"
#include "Bomb.h"

#define NO_DIRECTION 0		//玩家动作方向
#define LEFT 1			
#define RIGHT 2
#define UP 3
#define DOWN 4

#define USER 0			//人物身份
#define COMPUTER 1

#define RED 1			//人物队属
#define GREEN 2
#define BLUE 3
#define YELLOW 4

#define STATE_FREE 0	//人物状态
#define STATE_BOXED 1
#define STATE_DIED 2

#define TOOL_SHOE 0		//道具种类
#define TOOL_BOMB 1
#define TOOL_LIQUID 2 

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

	float speed;//速度
	Bomb* myBomb;//炸弹类型
	int killNum;//杀敌数
	int state;//状态
	int score;
	
	static Figure* createFigureSprite(Point position, int direction,int type, int team);//创建人物
	void figureInit(Point position, int direction, int type, int team);//初始化人物
	Animate* createAnimate(int direction, int team, const char*action, int num,int time);

	void Move(int myDirection, bool i);
	void DoStand();
	void SetBomb();
	void CollectTool(unsigned int i);
	void BeBoxed();
	void BeSaved();
	void Die();
	void Win();
	void Delete();


	virtual bool init();
	CREATE_FUNC(Figure);
};
#endif // !_FIGURE_H_INCLUDED
