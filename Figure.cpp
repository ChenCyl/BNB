#include "Figure.h"
USING_NS_CC;

Figure::Figure()
{
}


Figure::~Figure()
{
}

Figure* Figure::createFigureSprite(Point position, int direction, int type, int team,int tag) {
	Figure* figure = new Figure();
	if (figure&&figure->init()) {
		figure->autorelease();
		figure->figureInit(position, direction, type, team,tag);
		return figure;
	}
	CC_SAFE_DELETE(figure);
	return NULL;
}

void Figure::figureInit(Point myPosition, int myDirection, int myType, int myTeam,int mytag) {
	position = myPosition;
	direction = myDirection;
	type = myType;
	team = myTeam;
	tag = mytag;
	speed = 10.0;
	bombNum = 1;
	bombNum_avail = 1;
	bombPower = 1;
	killNum = 0;
	state = STATE_FREE;
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("figure.plist", "figure.png");
	sprite = Sprite::createWithSpriteFrameName(String::createWithFormat("stand%d%d1.png", team, direction)->getCString());
	sprite->setPosition(position);
	sprite->setAnchorPoint(ccp(0.4, 0.3));
	addChild(sprite,1);

	labelInit(mytag);
}

Animate* Figure::createAnimate(int direction, int team, const char*action, int num,int time) {
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("figure.plist", "figure.png");
	Vector<SpriteFrame*> frameArray;
	for (int i = 1;i <= num;i++) {
		auto* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("%s%d%d%d.png", action, team, direction, i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(time);
	animation->setDelayPerUnit(0.1f);
	return Animate::create(animation);
}

void Figure::Move(int myDirection, bool i) {
	direction = myDirection;
	if (state == STATE_FREE) {
		sprite->stopAllActions();
		auto* walk = createAnimate(direction, team, "walk", 4, -1);
		Point target;

		if (i) {
			switch (direction) {
			case LEFT:
				target = Vec2(position.x - speed, position.y);
				break;
			case RIGHT:
				target = Vec2(position.x + speed, position.y);
				break;
			case UP:
				target = Vec2(position.x, position.y + speed);
				break;
			case DOWN:
				target = Vec2(position.x, position.y - speed);
				break;
			}
			auto* moveto = MoveTo::create(1.0 / 6, target);
			auto* spawn = Spawn::create(moveto, walk, NULL);
			sprite->runAction(spawn);
			position = target;
		}
		else {
			sprite->runAction(walk);
		}
	}
}

void Figure::DoStand() {
	sprite->stopAllActions();
	auto* stand = createAnimate(direction, team, "stand", 1, -1);
	sprite->runAction(stand);
}

void Figure::CollectTool(unsigned int tool_type) {
	switch (tool_type)
	{
	case TOOL_SHOE:
	{
		speed < 17 ? speed += 2.5 : speed+=0;
		break;
	}
	case TOOL_BOMB:
	{	
		if (bombNum <= 10) {
			++bombNum;
			++bombNum_avail;
			updateLabel();
		}
		break;
	}
	case TOOL_LIQUID:
	{
		bombPower <= 6?++bombPower:bombPower+=0;
		break;
	}
	default:
		break;
	}
}

void Figure::BeBoxed() {
	state = STATE_BOXED;
	sprite->stopAllActions();
	auto* beboxed = createAnimate(NO_DIRECTION, team, "beboxed", 4,-1); 
	sprite->runAction(beboxed);
	scheduleOnce(schedule_selector(Figure::Die), 9.0f);
}

void Figure::Die(float dt) {
	if (state != STATE_BOXED) {
		return;
	}
	state = STATE_DIED;
	sprite->stopAllActions();
	auto* died = createAnimate(NO_DIRECTION, team, "died", 5,1); 
	position = Vec2(4000, 4000);
	auto* callFunc = CallFunc::create(CC_CALLBACK_0(Figure::Delete, this));
	auto* sequence = Sequence::create(died, callFunc, NULL);
	sprite->runAction(sequence);
}

void Figure::BeSaved() {
	state = STATE_FREE;
	sprite->stopAllActions();
	auto* besaved = createAnimate(NO_DIRECTION, team, "besaved", 3,1); 
	auto* callFunc = CallFunc::create(CC_CALLBACK_0(Figure::DoStand, this));
	auto* sequence = Sequence::create(besaved, callFunc, NULL);
	sprite->runAction(sequence);
}

void Figure::Win() {
	state = STATE_FREE;
	sprite->stopAllActions();
	auto* win = createAnimate(NO_DIRECTION, team, "win", 2,-1); 
	sprite->runAction(win);
}

bool Figure::init() {
	if (!Layer::init()) {
		return false;
	}
	return true;
}

void Figure::Delete() {
	removeChild(sprite, true);
}

void Figure::labelInit(int tag) {

	labelBombNum = LabelTTF::create("bomb 1", "Arial", 15);
	labelBombNum->setAnchorPoint(Vec2(0.5, 0.5));
	labelBombNum->setFontFillColor(Color3B(240, 248, 255));
	labelBombNum->setPosition(Vec2(730, 85 + tag * 105));
	addChild(labelBombNum, 4);
	labelBombNum_avail = LabelTTF::create("bombAvail 1", "Arial", 15);
	labelBombNum_avail->setAnchorPoint(Vec2(0.5, 0.5));
	labelBombNum_avail->setFontFillColor(Color3B(240, 248, 255));
	labelBombNum_avail->setPosition(Vec2(730, 100 + tag * 105));
	addChild(labelBombNum_avail, 4);
}

void Figure::updateLabel() {
	auto* bombNumStr = String::createWithFormat("bomb %d", bombNum)->getCString();
	labelBombNum->setString(bombNumStr);
	bombNumStr = String::createWithFormat("bombAvail %d", bombNum_avail)->getCString();
	labelBombNum_avail->setString(bombNumStr);
}