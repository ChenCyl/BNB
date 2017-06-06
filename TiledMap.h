#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <vector>
#include <map>
#include "cocos2d.h"
#define LEFT 1			
#define RIGHT 2
#define UP 3
#define DOWN 4
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

	std::vector<int> calculateBombRange(int x, int y);
	CREATE_FUNC(TiledMap);
public:
	//���Ե�ͼ
	cocos2d::TMXTiledMap* _map;
	//��ʽ��ͼ
	std::vector<cocos2d::TMXTiledMap*> _mapVec;
	//�ϰ��͵��߲�
	cocos2d::TMXLayer* _collisionAndProp;
	//����������
	float _figureOriginX;
	float _figureOriginY;
	//ÿ��λ�õ�����Ʒ�Χ0123��������
	std::map<cocos2d::Point, std::vector<int>> m_bombRange;//��Ƭ��ͼʽ����
};

#endif // __HELLOWORLD_SCENE_H__
