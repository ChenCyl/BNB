#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <vector>
#include <map>
#include "cocos2d.h"
#define LEFT 1			
#define RIGHT 2
#define UP 3
#define DOWN 4

#define TOOL_SHOE 1		//��������
#define TOOL_BOMB 2
#define TOOL_LIQUID 3 
class TiledMap : public cocos2d::Layer
{
public:
    virtual bool init();
	//ת������
	static TiledMap* createTiledMap();
	cocos2d::Point tileCoordFromPosition(cocos2d::Point position);
	cocos2d::Point PositionFromTileCoord(cocos2d::Point pos);
	//�ж��Ƿ�Ϊ�ϰ�
	bool isCollision(cocos2d::Point pos, int direction);
	//ը������
	void bombTheProp(cocos2d::Point bombPos, int bombPower);
	//����λ������е��ߣ��Ե����߲��ҷ��ص�������
	int eatTool(cocos2d::Point pos);

	//���㴫��λ�õı��Ʒ�Χ���������Ƚ�֮��ģ�
	std::vector<cocos2d::Point> calculateBomRangPoint(cocos2d::Point bombPos, int bombPower);

	//���㴫��λ�õ�����Ʒ�Χ0123��������
	std::vector<int> calculateBombRange(int x, int y);
	
	CREATE_FUNC(TiledMap);
public:
	//���Ե�ͼ
	cocos2d::TMXTiledMap* _map;
	//��ʽ��ͼ
	std::vector<cocos2d::TMXTiledMap*> _mapVec;
	//�ϰ��͵��߲�
	cocos2d::TMXLayer* _collisionAndProp;
	//�����
	cocos2d::TMXLayer* _land;
	//����������
	float _figureOriginX;
	float _figureOriginY;
	//ÿ��λ�õ�����Ʒ�Χ0123��������
	std::map<cocos2d::Point, std::vector<int>> m_bombRange;//��Ƭ��ͼʽ����
};

#endif // __HELLOWORLD_SCENE_H__
