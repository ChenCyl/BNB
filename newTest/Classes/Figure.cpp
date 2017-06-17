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
	switch (myTeam) {
	case RED:
	{
		speed += 2.5;
		score -= 15;
		break;
	}
	case BLUE:
	{
		++bombNum;
		++bombNum_avail;
		speed -= 5;
		break;
	}
	case GREEN:
	{
		speed -= 2.5;
		score += 15;
		break;
	}
	case YELLOW:
	{
		speed -= 2.5;
		++bombPower;
		break;
	}
	default:
		break;
	}
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
	score += 5;
	updateLabel();
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
	case TOOL_COIN:
	{
		score += 5;
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
	stopAllSchedules();
	auto* death = Sprite::create("death.png");
	death->setPosition(Vec2(730, 500 - tag * 110));
	addChild(death);
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
	SimpleAudioEngine::getInstance()->playEffect("effect9.wav");
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

	labelScore = LabelTTF::create(String::createWithFormat("Score %d", score)->getCString(), "Arial", 15);
	labelScore->setAnchorPoint(Vec2(0.5, 0.5));
	labelScore->setFontFillColor(Color3B(240, 248, 255));
	labelScore->setPosition(Vec2(790, 490 - tag * 110));
	addChild(labelScore, 4);
	labelBombNum_avail = LabelTTF::create(String::createWithFormat("Bomb %d", bombNum_avail)->getCString(), "Arial", 15);
	labelBombNum_avail->setAnchorPoint(Vec2(0.5, 0.5));
	labelBombNum_avail->setFontFillColor(Color3B(240, 248, 255));
	labelBombNum_avail->setPosition(Vec2(790, 470 - tag * 110));
	addChild(labelBombNum_avail, 4);
	labelKill = LabelTTF::create("Kill 0", "Arial", 15);
	labelKill->setAnchorPoint(Vec2(0.5, 0.5));
	labelKill->setFontFillColor(Color3B(240, 248, 255));
	labelKill->setPosition(Vec2(850, 490 - tag * 110));
	addChild(labelKill, 4);
	labelSave = LabelTTF::create("Save 0", "Arial", 15);
	labelSave->setAnchorPoint(Vec2(0.5, 0.5));
	labelSave->setFontFillColor(Color3B(240, 248, 255));
	labelSave->setPosition(Vec2(850, 470 - tag * 110));
	addChild(labelSave, 4);
	labelTag = LabelTTF::create(String::createWithFormat("ZZCYL%d", tag+1)->getCString(), "Arial", 15);
	labelTag->setAnchorPoint(Vec2(0.5, 0.5));
	labelTag->setFontFillColor(Color3B(240, 248, 255));
	labelTag->setPosition(Vec2(840, 520 - tag * 110));
	addChild(labelTag, 4);
	
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("figure.plist", "figure.png");
	Portrait = Sprite::createWithSpriteFrameName(String::createWithFormat("win%d01.png", team)->getCString());
	Portrait->setPosition(Vec2(730, 500 - tag * 110));
	Portrait->setScale(1.5);
	addChild(Portrait);
}

void Figure::updateLabel() {
	labelBombNum_avail->setString(String::createWithFormat("Bomb %d", bombNum_avail)->getCString());

	labelKill->setString(String::createWithFormat("Kill %d", killNum)->getCString());
	
	labelSave->setString(String::createWithFormat("Save %d", saveNum)->getCString());
	
	labelScore->setString(String::createWithFormat("Score %d", score)->getCString());
}

void Figure::stopAllSchedules() {
	unscheduleAllSelectors();
}

void Figure::gameover() {
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("figure.plist", "figure.png");
	sprite = Sprite::createWithSpriteFrameName(String::createWithFormat("stand%d41.png", team)->getCString());
	sprite->setPosition(Vec2(160, 320-tag*50));
	getParent()->addChild(sprite, 4);
	
	auto* Score= LabelTTF::create(String::createWithFormat("Score %d", score)->getCString(), "Arial", 15);
	Score->setAnchorPoint(Vec2(0.5, 0.5));
	Score->setFontFillColor(Color3B(240, 248, 255));
	Score->setPosition(Vec2(240, 320 - tag * 50));
	getParent()->addChild(Score, 4);

	auto* Kill = LabelTTF::create(String::createWithFormat("Kill %d", killNum)->getCString(), "Arial", 15);
	Kill->setAnchorPoint(Vec2(0.5, 0.5));
	Kill->setFontFillColor(Color3B(240, 248, 255));
	Kill->setPosition(Vec2(400, 320 - tag * 50));
	getParent()->addChild(Kill, 4);

	auto* Save = LabelTTF::create(String::createWithFormat("Save %d", saveNum)->getCString(), "Arial", 15);
	Save->setAnchorPoint(Vec2(0.5, 0.5));
	Save->setFontFillColor(Color3B(240, 248, 255));
	Save->setPosition(Vec2(320, 320 - tag * 50));
	getParent()->addChild(Save, 4);

}