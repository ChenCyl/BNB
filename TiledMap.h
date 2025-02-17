#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <vector>
#include <map>
#include "cocos2d.h"
#define LEFT 1			
#define RIGHT 2
#define UP 3
#define DOWN 4

#define TOOL_SHOE 1		//道具种类
#define TOOL_BOMB 2
#define TOOL_LIQUID 3 
class TiledMap : public cocos2d::Layer
{
public:
    virtual bool init();
	//转换坐标
	static TiledMap* createTiledMap(int mapType);
	cocos2d::Point tileCoordFromPosition(cocos2d::Point position);
	cocos2d::Point PositionFromTileCoord(cocos2d::Point pos);
	//判断是否为障碍
	bool isCollision(cocos2d::Point pos, int direction);
	//炸出道具
	void bombTheProp(cocos2d::Point bombPos, int bombPower);
	//所在位置如果有道具，吃掉道具并且返回道具类型
	int eatTool(cocos2d::Point pos);

	//计算传入位置的爆破范围
	std::vector<cocos2d::Point> calculateBomRangPoint(cocos2d::Point bombPos, int bombPower);
	
	CREATE_FUNC(TiledMap);
public:
	//地图编号
	int _num;
	//地图
	cocos2d::TMXTiledMap* _map;
	//地图集
	std::vector<cocos2d::TMXTiledMap*> _mapVec;
	//障碍和道具层
	cocos2d::TMXLayer* _collisionAndProp;
	//地面层
	cocos2d::TMXLayer* _land;
	//遮挡层
	cocos2d::TMXLayer* _dang;
	//对象层的坐标
	std::vector<cocos2d::Point> _figureOriginCoord;
	//每个位置的最大爆破范围0123左右上下
	//std::map<cocos2d::Point, std::vector<int>> m_bombRange;//瓦片地图式坐标
	std::vector<int> _bombRange;//1.定范围 2.能不能炸开 3.炸的是道具还是盒子
};

#endif // __HELLOWORLD_SCENE_H__
