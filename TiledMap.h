#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <vector>
#include "cocos2d.h"

class TiledMap : public cocos2d::Layer
{
public:
    virtual bool init();

	//virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	//virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	//virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	//cocos2d::Sprite *_sprite;

    // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	/*void update(float delta) override;
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void keyPressedDuration(cocos2d::EventKeyboard::KeyCode keyCode);
*/
	cocos2d::Point tileCoordFromPosition(cocos2d::Point position);
	cocos2d::Point PositionFromTileCoord(cocos2d::Point pos);
	bool isCollision(cocos2d::Point pos);
	void bombTheProp(Point bombPos, std::vector<int> num);


	//放置炮弹
	/*void placeBomb();*/

	//void setProperties(cocos2d::Point pos);

    // implement the "static create()" method manually
    CREATE_FUNC(TiledMap);
public:
	cocos2d::TMXTiledMap* _map;//测试
	std::vector<cocos2d::TMXTiledMap*> _mapVec;
	cocos2d::TMXLayer* _collidable;
	cocos2d::TMXLayer* _propertiesLayer;
	float figureOriginX;//将人物加入到地图层会失败
	float figureOriginY;
};

#endif // __HELLOWORLD_SCENE_H__
