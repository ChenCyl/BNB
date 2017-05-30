#include "Bomb.h"

USING_NS_CC;

Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}

bool Bomb::init() {
	if (!Layer::init()) {
		return false;
	}
	return true;
}
Bomb* Bomb::createBombSprite(Point myposition) {
	Bomb* myBomb = new Bomb();
	if (myBomb&&myBomb->init()) {
		myBomb->autorelease();
		myBomb->bomb = Sprite::create("bomb1.png");
		myBomb->bomb->setPosition(myposition);
		myBomb->addChild(myBomb->bomb);
		myBomb->position = myposition;
		return myBomb;
	}
	CC_SAFE_DELETE(myBomb);
	return NULL;
}
void Bomb::addChildExplosion(float beg, float end, float remain,int tag) {
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("bomb.plist", "bomb.png");
	for (float i = beg;i < end;i+=40) {
		Sprite* sprite = Sprite::createWithSpriteFrameName(String::createWithFormat("%d.png", tag)->getCString());
		explosionSprite.push_back(sprite);
		if (tag == explode_line_left || tag == explode_line_right) {
			sprite->setPosition(Vec2(i, remain));
		}
		else {
			sprite->setPosition(Vec2(remain,i));
		}
		addChild(sprite);
	}
}
void Bomb::addExplosionAnimate(Point aniPosition, int tag) {
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("bomb.plist", "bomb.png");
	Sprite* sprite = Sprite::createWithSpriteFrameName(String::createWithFormat("%d.png", tag)->getCString());
	explosionSprite.push_back(sprite);
	sprite->setPosition(aniPosition);
	addChild(sprite);
	Vector<SpriteFrame*> frameArray;
	for (int i = 1;i <= 4;i++) {
		auto* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("%d%d.png", tag, i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.12f);
	auto animate = Animate::create(animation);
	sprite->runAction(animate);
}

void Bomb::explode(std::vector<Point>&vec) {
	addChildExplosion(vec[0].x+40, position.x, position.y, explode_line_left);
	addChildExplosion(position.x+40, vec[1].x, position.y, explode_line_right);
	addChildExplosion(position.y + 40, vec[2].y, position.x, explode_row_up);
	addChildExplosion(vec[3].y+40, position.y, position.x, explode_row_down);
	addExplosionAnimate(vec[0], explode_end_left);
	addExplosionAnimate(vec[1], explode_end_right);
	addExplosionAnimate(vec[2], explode_end_up);
	addExplosionAnimate(vec[3], explode_end_down);
}

void Bomb::bombDynamic() {
	bomb->stopAllActions();
	auto* action = createAnimate("bombDynamic", 3,-1);
	bomb->runAction(action);
}
void Bomb::bombExplode() {
	bomb->stopAllActions();
	auto* action = createAnimate("bombExplode", 4,1);
	auto* callFunc = CallFunc::create(CC_CALLBACK_0(Bomb::deleteBomb, this));
	auto* sequence = Sequence::create(action, callFunc, NULL);
	bomb->runAction(sequence);
}
Animate* Bomb::createAnimate(const char *action, int num,int time) {
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("bomb.plist", "bomb.png");
	Vector<SpriteFrame*> frameArray;
	for (int i = 1;i <= num;i++) {
		auto* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("%s%d.png",action, i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(time);
	animation->setDelayPerUnit(0.2f);
	return Animate::create(animation);
}
void Bomb::deleteBomb() {
	removeChild(bomb,true);
}
void Bomb::deleteExplode() {
	auto it = explosionSprite.begin();
	while (it != explosionSprite.end()) {
		removeChild(*it, true);
		++it;
	}
}