#include "Bomb.h"

USING_NS_CC;

Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}

Bomb* Bomb::create(const char* FileName) {
	Bomb* sprite = new Bomb();
	if (sprite&&sprite->initWithFile(FileName)) {
		sprite->bombNum = 1;
		sprite->bombNum_avail = 1;
		sprite->bombPower = 1;
		sprite->retain();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void Bomb::explode(std::vector<Point> &vec_positions, std::vector<int> &vec_types){
	for (int i = 0;i<vec_types.size();++i) {
		switch (vec_types[i]) {
		case explode_end_left:
//			Sprite* explotions=Sprite::create("----.png");
//			addChild(explotions);
			break;
		case explode_end_right:
			//			Sprite* explotions=Sprite::create("----.png");
			//			addChild(explotions);
			break;
		case explode_end_up:
			//			Sprite* explotions=Sprite::create("----.png");
			//			addChild(explotions);
			break;
		case explode_end_down:
			//			Sprite* explotions=Sprite::create("----.png");
			//			addChild(explotions);
			break;
		case explode_line:
			//			Sprite* explotions=Sprite::create("----.png");
			//			addChild(explotions);
			break;
		case explode_row:
			//			Sprite* explotions=Sprite::create("----.png");
			//			addChild(explotions);
			break;
		}

	}
}
void Bomb::bombDynamic() {
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("bomb.plist", "bomb.png");
	Vector<SpriteFrame*> frameArray;
	for (int i = 1;i <= 3;i++) {
		auto* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("bombDynamic%d", i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.4f);
	auto* action = Animate::create(animation);
	runAction(action);
}
void Bomb::bombExplode() {
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("bomb.plist", "bomb.png");
	Vector<SpriteFrame*> frameArray;
		for (int i = 1;i <= 4;i++) {
			auto* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("bombExplode%d", i)->getCString());
			frameArray.pushBack(frame);
		}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.4f);
	auto* action = Animate::create(animation);
	runAction(action);
}
