#include "TiledMap.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <stdlib.h>
#include <ctime>
#include <vector>
USING_NS_CC;

// on "init" you need to initialize your instance
bool TiledMap::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	_map = TMXTiledMap::create("map1.tmx");
	addChild(_map);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TMXObjectGroup* group = _map->getObjectGroup("object");
	ValueMap spawnPoint = group->getObject("friend");

	figureOriginX = spawnPoint["x"].asFloat();
	figureOriginY = spawnPoint["y"].asFloat();

	//_sprite = Sprite::create("friend_01.png");
	//_sprite->setAnchorPoint(ccp(0.5, 0.36));
	//_sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	/*_sprite->setPosition(x, y);
	this->addChild(_sprite);*/

	_collidable = _map->getLayer("layer2");
	_collidable->setVisible(true);

	_propertiesLayer = _map->getLayer("layer3");

	////单点触摸开启
	//setTouchEnabled(true);
	//setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//单点触摸

	/*auto dispatcher = Director::getInstance()->getEventDispatcher();;
	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	dispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);*/
	//auto listener = EventListenerKeyboard::create();
	//listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
	//	keys[keyCode] = true;
	//};
	//listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
	//	keys[keyCode] = false;
	//};
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//this->scheduleUpdate();
    ///////////////////////////////
    //// 2. add a menu item with "X" image, which is clicked to quit the program
    ////    you may modify it.

    //// add a "close" icon to exit the progress. it's an autorelease object
    //auto closeItem = MenuItemImage::create(
    //                                       "CloseNormal.png",
    //                                       "CloseSelected.png",
    //                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    //
    //closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
    //                            origin.y + closeItem->getContentSize().height/2));

    //// create menu, it's an autorelease object
    //auto menu = Menu::create(closeItem, NULL);
    //menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);

    ///////////////////////////////
    //// 3. add your codes below...

    //// add a label shows "Hello World"
    //// create and initialize a label
    //
    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    //
    //// position the label on the center of the screen
    //label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - label->getContentSize().height));

    //// add the label as a child to this layer
    //this->addChild(label, 1);

    //// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

    //// position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //// add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
    return true;
}


void TiledMap::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
//void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
//	if (EventKeyboard::KeyCode::KEY_SPACE == keyCode) {
//		CCLOG("Pressed: SPACE");
//	}
//}
//void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
//	if (EventKeyboard::KeyCode::KEY_UP_ARROW == keyCode) {
//		CCLOG("Released: ->");
//	}
//}
//void HelloWorld::update(float delta) {
//	Node::update(delta);
//	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
//	auto rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
//	auto upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW;
//	auto downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
//	auto space = EventKeyboard::KeyCode::KEY_SPACE;
//	if (isKeyPressed(leftArrow)) {
//		keyPressedDuration(leftArrow);
//	}
//	else if (isKeyPressed(rightArrow)) {
//		keyPressedDuration(rightArrow);
//	}
//	else if (isKeyPressed(upArrow)) {
//		keyPressedDuration(upArrow);
//	}
//	else if (isKeyPressed(downArrow)) {
//		keyPressedDuration(downArrow);
//	}
//	else if (isKeyPressed(space)) {
//		keyPressedDuration(space);
//	}
//}
//bool HelloWorld::isKeyPressed(EventKeyboard::KeyCode keyCode) {
//	return keys[keyCode];
//}
//void HelloWorld::keyPressedDuration(EventKeyboard::KeyCode keyCode) {
//	int offsetX = 0, offsetY = 0;
//	auto playerPosForCol = Vec2(_sprite->getPositionX() + offsetX, _sprite->getPositionY() + offsetY);
//	switch (keyCode)
//	{
//	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
//		offsetX = -5;
//		playerPosForCol = Vec2(_sprite->getPositionX() + offsetX - _map->getTileSize().width / 2, _sprite->getPositionY() + offsetY);
//		break;
//	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
//		offsetX = 5;
//		playerPosForCol = Vec2(_sprite->getPositionX() + offsetX + _map->getTileSize().width / 2, _sprite->getPositionY() + offsetY);
//		break;
//	case EventKeyboard::KeyCode::KEY_UP_ARROW:
//		offsetY = 5;
//		playerPosForCol = Vec2(_sprite->getPositionX() + offsetX, _sprite->getPositionY() + offsetY + _map->getTileSize().height / 2);
//		break;
//	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
//		offsetY = -5;
//		playerPosForCol = Vec2(_sprite->getPositionX() + offsetX, _sprite->getPositionY() + offsetY - _map->getTileSize().height / 2);
//		break;
//	case EventKeyboard::KeyCode::KEY_SPACE:
//		placeBomb();
//		break;
//	default:
//		offsetY = offsetX = 0;
//		break;
//	}
//	auto playerPos = Vec2(_sprite->getPositionX() + offsetX, _sprite->getPositionY() + offsetY);
//	if (!this->isCollision(playerPosForCol)) {
//		auto moveTo = MoveTo::create(0, playerPos);
//		_sprite->runAction(moveTo);
//	}
//}

//bool HelloWorld::onTouchBegan(Touch *touch, Event *event) {
//	
//	return true;
//}
//void HelloWorld::onTouchMoved(Touch *touch, Event *event) {
//
//}
//void HelloWorld::onTouchEnded(Touch *touch, Event *event) {
//	Vec2 touchLocation = touch->getLocation();
	/*Vec2 playerPos = _sprite->getPosition();
	Vec2 diff = touchLocation - playerPos;

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += _map->getTileSize().width;
			_sprite->runAction(FlipX::create(false));
		}
		else {
			playerPos.x -= _map->getTileSize().width;
			_sprite->runAction(FlipX::create(true));
		}
	}
	else {
		if (diff.y > 0) {
			playerPos.y += _map->getTileSize().height;
		}
		else {
			playerPos.y -= _map->getTileSize().height;
		}
	}
	this->setPlayerPosition(playerPos);*/
	
	//单击使图块变化
//////////////////////////////////////////////////////////////////////////
	/*Point tileCoord = this->tileCoordFromPosition(touchLocation);
	int tileGid = _collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0) {
		Value prop = _map->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string canExplode = propValueMap["CanExplode"].asString();
		if (canExplode == "true") {
			srand((int)time(NULL));
			int gid = rand() % 6 + 10;
			_collidable->removeTileAt(tileCoord);*/
////////////////////////////////////////////////////////////////////////////
			//_propertiesLayer->setTileGID(gid, tileCoord);
			//_collidable->setTileGID(gid, tileCoord);
	

//键盘操作有关
bool TiledMap::isCollision(Point pos){
	Point tileCoord = this->tileCoordFromPosition(pos);
	int tileGid = _collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0) {
		//Value prop = _map->getPropertiesForGID(tileGid);
		//ValueMap propValueMap = prop.asValueMap();

		//std::string collision = propValueMap["Collidable"].asString();

		//if (collision == "true") {
		//	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
		//	return true;
		//}
		return true;
	}
	return false;
}

//鼠标单击移动有关
//void HelloWorld::setPlayerPosition(Point position) {
//	Point tileCoord = this->tileCoordFromPosition(position);
//	int tileGid = _collidable->getTileGIDAt(tileCoord);
//
//	if (tileGid > 0) {
//		Value prop = _map->getPropertiesForGID(tileGid);
//		ValueMap propValueMap = prop.asValueMap();
//
//		std::string collision = propValueMap["Collidable"].asString();
//
//		if (collision == "true") {
//			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
//			return;
//		}
//	}
//	_sprite->setPosition(position);
//}
Point TiledMap::tileCoordFromPosition(Point position) {
	int x = position.x / _map->getTileSize().width;
	int y = ((_map->getMapSize().height * _map->getTileSize().height) - position.y) / _map->getTileSize().height;
	return Point(x, y);
}
Point TiledMap::PositionFromTileCoord(Point pos) {
	int x = pos.x * 40 + 20;
	int y = (13 - pos.y) * 40 - 20;
	return Point(x, y);
}
void TiledMap::bombTheProp(Point bombPos, std::vector<int> num) {//传入炮弹的position和上下左右能炸的数量
	for (int i = -num[0]; i <= num[1]; i++) {
		if (i == 0) {
			continue;
		}
		Point tileCoord = this->tileCoordFromPosition(bombPos);
		int tileGid = _collidable->getTileGIDAt(Point(tileCoord.x + i, tileCoord.y));
		if (tileGid > 0) {
			Value prop = _map->getPropertiesForGID(tileGid);
			ValueMap propValueMap = prop.asValueMap();
			std::string canExplode = propValueMap["CanExplode"].asString();			
			if (canExplode == "true") {	
				srand((int)time(NULL));
				int gid = rand() % 6 + 10;
				_collidable->setTileGID(gid, tileCoord);
			}
		}
	}
	for (int i = -num[3]; i <= num[2]; i++) {
		if (i == 0) {
			continue;
		}
		Point tileCoord = this->tileCoordFromPosition(bombPos);
		int tileGid = _collidable->getTileGIDAt(Point(tileCoord.x, tileCoord.y + i));
		if (tileGid > 0) {
			Value prop = _map->getPropertiesForGID(tileGid);
			ValueMap propValueMap = prop.asValueMap();
			std::string canExplode = propValueMap["CanExplode"].asString();
			if (canExplode == "true") {
				srand((int)time(NULL));
				int gid = rand() % 6 + 10;
				_collidable->setTileGID(gid, tileCoord);
			}
		}
	}
}

//void HelloWorld::setProperties(Point pos) {
//	srand((int)time(NULL));
//	Point truePositionFromTileCoord = Vec2(pos.x * 40 + 20, (13 - pos.y) * 40 - 20);
//	_properties[rand() % 1]->setPosition(truePositionFromTileCoord);
//}
//void HelloWorld::placeBomb() {
//	Point bombPos = _sprite->getPosition();
//	Point tileCoord = this->tileCoordFromPosition(bombPos);
//	_collidable->setTileGID(10, tileCoord);
// }
