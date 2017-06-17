#include "TiledMap.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "chooselayer.h"
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
	//_num = 2;//从choselayer中传入
	_mapVec.push_back(TMXTiledMap::create("map1.tmx"));
	_mapVec.push_back(TMXTiledMap::create("map2.tmx"));
	_mapVec.push_back(TMXTiledMap::create("map3.tmx"));
	_map = _mapVec[_num - 1];
	addChild(_map);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TMXObjectGroup* group = _map->getObjectGroup("object");
	ValueMap spawnPoint1 = group->getObject("figure1");
	ValueMap spawnPoint2 = group->getObject("figure2");
	ValueMap spawnPoint3 = group->getObject("figure3");
	ValueMap spawnPoint4 = group->getObject("figure4");
	_figureOriginCoord.push_back(Vec2(spawnPoint1["x"].asFloat(), spawnPoint1["y"].asFloat()));
	_figureOriginCoord.push_back(Vec2(spawnPoint2["x"].asFloat(), spawnPoint2["y"].asFloat()));
	_figureOriginCoord.push_back(Vec2(spawnPoint3["x"].asFloat(), spawnPoint3["y"].asFloat()));
	_figureOriginCoord.push_back(Vec2(spawnPoint4["x"].asFloat(), spawnPoint4["y"].asFloat()));

	_collisionAndProp = _map->getLayer("layer2");
	_collisionAndProp->setVisible(true);
	_land = _map->getLayer("layer1");
	_dang = _map->getLayer("layer3");

	//初始化m_bombRange坐标是瓦片地图式以左上角为零点
	/*for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 13; j++) {
			m_bombrange[vec2(i, j)] = calculatebombrange(i, j);
		}
	}*/

    return true;
}
TiledMap* TiledMap::createTiledMap(int _num) {
	TiledMap* tiledMap = new TiledMap();
	tiledMap->_num = _num;
	if (tiledMap&&tiledMap->init()) {
		tiledMap->autorelease();
		return tiledMap;
	}
	CC_SAFE_DELETE(tiledMap);
	return NULL;
}

bool TiledMap::isCollision(cocos2d::Point pos, int direction) {
	Point tileCoord1;
	Point tileCoord2;
	Point tileCoord3;
	switch (direction) {
	case LEFT:
		tileCoord1 = this->tileCoordFromPosition(Vec2(pos.x - 20, pos.y));
		tileCoord2 = this->tileCoordFromPosition(Vec2(pos.x - 10, pos.y + 10));
		tileCoord3 = this->tileCoordFromPosition(Vec2(pos.x - 10, pos.y - 10));
		break;
	case RIGHT:
		tileCoord1 = this->tileCoordFromPosition(Vec2(pos.x + 20, pos.y));
		tileCoord2 = this->tileCoordFromPosition(Vec2(pos.x + 10, pos.y + 10));
		tileCoord3 = this->tileCoordFromPosition(Vec2(pos.x + 10, pos.y - 10));
		break;
	case UP:
		tileCoord1 = this->tileCoordFromPosition(Vec2(pos.x, pos.y + 20));
		tileCoord2 = this->tileCoordFromPosition(Vec2(pos.x + 10, pos.y + 10));
		tileCoord3 = this->tileCoordFromPosition(Vec2(pos.x - 10, pos.y + 10));
		break;
	case DOWN:
		tileCoord1 = this->tileCoordFromPosition(Vec2(pos.x, pos.y - 20));
		tileCoord2 = this->tileCoordFromPosition(Vec2(pos.x + 10, pos.y - 10));
		tileCoord3 = this->tileCoordFromPosition(Vec2(pos.x - 10, pos.y - 10));
		break;
	}
	int tileGid1 = _collisionAndProp->getTileGIDAt(tileCoord1);
	int tileGid2 = _collisionAndProp->getTileGIDAt(tileCoord2);
	int tileGid3 = _collisionAndProp->getTileGIDAt(tileCoord3);

	if (tileGid1 > 0) {
		Value prop1 = _map->getPropertiesForGID(tileGid1);
		ValueMap propValueMap1 = prop1.asValueMap();

		std::string collision1 = propValueMap1["Collidable"].asString();

		if (collision1 == "true") {
			return true;
		}
	}
	if (tileGid2 > 0) {
		Value prop2 = _map->getPropertiesForGID(tileGid2);
		ValueMap propValueMap2 = prop2.asValueMap();

		std::string collision2 = propValueMap2["Collidable"].asString();

		if (collision2 == "true") {
			return true;
		}
	}
	if (tileGid3 > 0) {
		Value prop3 = _map->getPropertiesForGID(tileGid3);
		ValueMap propValueMap3 = prop3.asValueMap();

		std::string collision3 = propValueMap3["Collidable"].asString();

		if (collision3 == "true") {
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
					_dang->removeTileAt(Point(tileCoord.x + i, tileCoord.y - 1));
				}
				else {
					int gid = rand() % 8 + 21;//8个随机数从gid=21开始，有3个是道具，5个是空白
					_collisionAndProp->setTileGID(gid, Point(tileCoord.x + i, tileCoord.y));
					_dang->setTileGID(gid + 26, Point(tileCoord.x + i, tileCoord.y - 1));
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
					_dang->removeTileAt(Point(tileCoord.x, tileCoord.y + i - 1));
				}
				else {
					int gid = rand() % 8 + 21;//8个随机数从gid=21开始，有3个是道具，5个是空白
					_collisionAndProp->setTileGID(gid, Point(tileCoord.x, tileCoord.y + i));
					_dang->setTileGID(gid + 26, Point(tileCoord.x, tileCoord.y + i - 1));
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
			_dang->removeTileAt(Vec2(tileCoord.x, tileCoord.y - 1));
			return TOOL_SHOE;
		}
		if (tool == "bomb") {
			_collisionAndProp->removeTileAt(tileCoord);
			_dang->removeTileAt(Vec2(tileCoord.x, tileCoord.y - 1));
			return TOOL_BOMB;
		}
		if (tool == "liquid") {
			_collisionAndProp->removeTileAt(tileCoord);
			_dang->removeTileAt(Vec2(tileCoord.x, tileCoord.y - 1));
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