#include "TiledMap.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <map>
USING_NS_CC;

// on "init" you need to initialize your instance
bool TiledMap::init()
{
	if (!Layer::init())
	{
		return false;
	}
	_num = 2;//从choselayer中传入
	_mapVec.push_back(TMXTiledMap::create("map1.tmx"));
	_mapVec.push_back(TMXTiledMap::create("map2.tmx"));
	_map = _mapVec[_num - 1];
	addChild(_map);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TMXObjectGroup* group = _map->getObjectGroup("object");
	ValueMap spawnPoint1 = group->getObject("figure1");
	ValueMap spawnPoint2 = group->getObject("figure2");
	ValueMap spawnPoint3 = group->getObject("friend3");
	ValueMap spawnPoint4 = group->getObject("friend4");
	_figureOriginCoord.push_back(Vec2(spawnPoint1["x"].asFloat(), spawnPoint1["y"].asFloat()));
	_figureOriginCoord.push_back(Vec2(spawnPoint2["x"].asFloat(), spawnPoint2["y"].asFloat()));
	_figureOriginCoord.push_back(Vec2(spawnPoint3["x"].asFloat(), spawnPoint3["y"].asFloat()));
	_figureOriginCoord.push_back(Vec2(spawnPoint4["x"].asFloat(), spawnPoint4["y"].asFloat()));

	_collisionAndProp = _map->getLayer("layer2");
	_collisionAndProp->setVisible(true);
	_land = _map->getLayer("layer1");

	//初始化m_bombRange坐标是瓦片地图式以左上角为零点
	/*for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 13; j++) {
			m_bombrange[vec2(i, j)] = calculatebombrange(i, j);
		}
	}*/

    return true;
}
TiledMap* TiledMap::createTiledMap() {
	TiledMap* tiledMap = new TiledMap();
	if (tiledMap&&tiledMap->init()) {
		tiledMap->autorelease();
		return tiledMap;
	}
	CC_SAFE_DELETE(tiledMap);
	return NULL;
}

bool TiledMap::isCollision(cocos2d::Point pos, int direction) {
	Point tileCoord;
	switch (direction) {
	case LEFT:
		tileCoord = this->tileCoordFromPosition(Vec2(pos.x - 20, pos.y));
		break;
	case RIGHT:
		tileCoord = this->tileCoordFromPosition(Vec2(pos.x + 20, pos.y));
		break;
	case UP:
		tileCoord = this->tileCoordFromPosition(Vec2(pos.x, pos.y + 15));
		break;
	case DOWN:
		tileCoord = this->tileCoordFromPosition(Vec2(pos.x, pos.y - 15));
		break;
	}
	int tileGid = _collisionAndProp->getTileGIDAt(tileCoord);

	if (tileGid > 0) {
		Value prop = _map->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();

		if (collision == "true") {
			return true;
		}
	}
	return false;
}

Point TiledMap::tileCoordFromPosition(Point position) {
	/*int x = (position.x - 20 ) / _map->getTileSize().width;
	int y = ((_map->getMapSize().height * _map->getTileSize().height) - (position.y - 40)) / _map->getTileSize().height;
	return Point(x, y);*/
	int x = position.x / _map->getTileSize().width;
	int y = ((_map->getMapSize().height * _map->getTileSize().height) - position.y) / _map->getTileSize().height;
	return Point(x, y);
}
Point TiledMap::PositionFromTileCoord(Point pos) {
	int x = pos.x * _map->getTileSize().width + _map->getTileSize().width / 2;
	int y = (_map->getMapSize().height - pos.y) *  _map->getTileSize().height - _map->getTileSize().height / 2;
	return Point(x, y);
}

void TiledMap::bombTheProp(Point bombPos, int bombPower) {//传入炮弹的position和bombpower
	srand((int)time(NULL));
	Point tileCoord = this->tileCoordFromPosition(bombPos);
	for (int i = -_bombRange[0]; i <= _bombRange[1]; i++) {
		if (i == 0) {
			continue;
		}
		int tileGid = _collisionAndProp->getTileGIDAt(Point(tileCoord.x + i, tileCoord.y));
		if (tileGid > 0) {
			Value prop = _map->getPropertiesForGID(tileGid);
			ValueMap propValueMap = prop.asValueMap();
			std::string canExplode = propValueMap["CanExplode"].asString();			
			std::string tool = propValueMap["Tool"].asString();
			if (canExplode == "true") {	
				if (tool == "shoe" || tool == "liquid" || tool == "bomb") {
					_collisionAndProp->removeTileAt(Point(tileCoord.x + i, tileCoord.y));
				}
				else {
					int gid = rand() % 8 + 21;//8个随机数从gid=21开始，有3个是道具，5个是空白
					_collisionAndProp->setTileGID(gid, Point(tileCoord.x + i, tileCoord.y));
				}
			}
		}
	}
	for (int i = -_bombRange[2]; i <= _bombRange[3]; i++) {
		if (i == 0) {
			continue;
		}
		int tileGid = _collisionAndProp->getTileGIDAt(Point(tileCoord.x, tileCoord.y + i));
		if (tileGid > 0) {
			Value prop = _map->getPropertiesForGID(tileGid);
			ValueMap propValueMap = prop.asValueMap();
			std::string canExplode = propValueMap["CanExplode"].asString();
			std::string tool = propValueMap["Tool"].asString();
			if (canExplode == "true") {
				if (tool == "shoe" || tool == "liquid" || tool == "bomb") {
					_collisionAndProp->removeTileAt(Point(tileCoord.x, tileCoord.y + i));
				}
				else {
					int gid = rand() % 8 + 21;//8个随机数从gid=21开始，有3个是道具，5个是空白
					_collisionAndProp->setTileGID(gid, Point(tileCoord.x, tileCoord.y + i));
				}
			}
		}
	}
}
//std::vector<int> TiledMap::calculateBombRange(int x, int y) {
//	int left = x, right = 14 - x, up = y, down = 12 - y;
//	std::vector<int> vec = { left, right, up, down};
//	int tileGid;
//	for (int i = 1; i <= left; i++) {
//		tileGid = _collisionAndProp->getTileGIDAt(Point(x - i, y));
//		if (tileGid > 0) {
//			Value prop = _map->getPropertiesForGID(tileGid);
//			ValueMap propValueMap = prop.asValueMap();
//			std::string canExplode = propValueMap["CanExplode"].asString();
//			if (canExplode == "false") {
//				left = i - 1;
//				break;
//			}
//		}
//	}
//	for (int i = 1; i <= right; i++) {
//		tileGid = _collisionAndProp->getTileGIDAt(Point(x + i, y));
//		if (tileGid > 0) {
//			Value prop = _map->getPropertiesForGID(tileGid);
//			ValueMap propValueMap = prop.asValueMap();
//			std::string canExplode = propValueMap["CanExplode"].asString();
//			if (canExplode == "false") {
//				right = i - 1;
//				break;
//			}
//		}
//	}
//	for (int i = 1; i <= up; i++) {
//		tileGid = _collisionAndProp->getTileGIDAt(Point(x, y - i));
//		if (tileGid > 0) {
//			Value prop = _map->getPropertiesForGID(tileGid);
//			ValueMap propValueMap = prop.asValueMap();
//			std::string canExplode = propValueMap["CanExplode"].asString();
//			if (canExplode == "false") {
//				up = i - 1;
//				break;
//			}
//		}
//	}
//	for (int i = 1; i <= down; i++) {
//		tileGid = _collisionAndProp->getTileGIDAt(Point(x, y + i));
//		if (tileGid > 0) {
//			Value prop = _map->getPropertiesForGID(tileGid);
//			ValueMap propValueMap = prop.asValueMap();
//			std::string canExplode = propValueMap["CanExplode"].asString();
//			if (canExplode == "false") {
//				down = i - 1;
//				break;
//			}
//		}
//	}
//	return vec;
//}
int TiledMap::eatTool(cocos2d::Point pos) {
	Point tileCoord = this->tileCoordFromPosition(pos);
	int tileGid = _collisionAndProp->getTileGIDAt(tileCoord);
	if (tileGid > 0) {
		Value prop = _map->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();
		std::string tool = propValueMap["Tool"].asString();
		if (tool == "shoe") {
			_collisionAndProp->removeTileAt(tileCoord);
			return TOOL_SHOE;
		}
		if (tool == "bomb") {
			_collisionAndProp->removeTileAt(tileCoord);
			return TOOL_BOMB;
		}
		if (tool == "liquid") {
			_collisionAndProp->removeTileAt(tileCoord);
			return TOOL_LIQUID;
		}
	}
	return 0;
}
//计算爆炸范围并初始化_bombRange
std::vector<Point> TiledMap::calculateBomRangPoint(Point bombPos,  int bombPower) {
	Point tileCoord = this->tileCoordFromPosition(bombPos);
	std::vector<int> temp(4, bombPower);
	_bombRange = temp;
	int tileGid;
	//左方向
	for (int i = 1; i <= bombPower; i++) {
		tileGid = _collisionAndProp->getTileGIDAt(Point(tileCoord.x - i, tileCoord.y));
		if (tileGid > 0) {
			Value prop = _map->getPropertiesForGID(tileGid);
			ValueMap propValueMap = prop.asValueMap();
			std::string collision = propValueMap["Collidable"].asString();
			std::string canExplode = propValueMap["CanExplode"].asString();
			if (collision == "true") {
				if (canExplode == "false") {
					_bombRange[0] = i - 1;
				}
				else {
					_bombRange[0] = i;
				}
				break;
			}
		}
	}
	//右
	for (int i = 1; i <= bombPower; i++) {
		tileGid = _collisionAndProp->getTileGIDAt(Point(tileCoord.x + i, tileCoord.y));
		if (tileGid > 0) {
			Value prop = _map->getPropertiesForGID(tileGid);
			ValueMap propValueMap = prop.asValueMap();
			std::string collision = propValueMap["Collidable"].asString();
			std::string canExplode = propValueMap["CanExplode"].asString();
			if (collision == "true") {
				if (canExplode == "false") {
					_bombRange[1] = i - 1;
				}
				else {
					_bombRange[1] = i;
				}
				break;
			}
		}
	}
	//上
	for (int i = 1; i <= bombPower; i++) {
		tileGid = _collisionAndProp->getTileGIDAt(Point(tileCoord.x, tileCoord.y - i));
		if (tileGid > 0) {
			Value prop = _map->getPropertiesForGID(tileGid);
			ValueMap propValueMap = prop.asValueMap();
			std::string collision = propValueMap["Collidable"].asString();
			std::string canExplode = propValueMap["CanExplode"].asString();
			if (collision == "true") {
				if (canExplode == "false") {
					_bombRange[2] = i - 1;
				}
				else {
					_bombRange[2] = i;
				}
				break;
			}
		}
	}
	//下
	for (int i = 1; i <= bombPower; i++) {
		tileGid = _collisionAndProp->getTileGIDAt(Point(tileCoord.x, tileCoord.y + i));
		if (tileGid > 0) {
			Value prop = _map->getPropertiesForGID(tileGid);
			ValueMap propValueMap = prop.asValueMap();
			std::string collision = propValueMap["Collidable"].asString();
			std::string canExplode = propValueMap["CanExplode"].asString();
			if (collision == "true") {
				if (canExplode == "false") {
					_bombRange[3] = i - 1;
				}
				else {
					_bombRange[3] = i;
				}
				break;
			}
		}
	}
	std::vector<Point> vec;
	vec.push_back(Vec2(bombPos.x - _bombRange[0] * _map->getTileSize().width, bombPos.y));
	vec.push_back(Vec2(bombPos.x + _bombRange[1] * _map->getTileSize().width, bombPos.y));
	vec.push_back(Vec2(bombPos.x, bombPos.y + _bombRange[2] * _map->getTileSize().height));
	vec.push_back(Vec2(bombPos.x, bombPos.y - _bombRange[3] * _map->getTileSize().height));
	return vec;
}