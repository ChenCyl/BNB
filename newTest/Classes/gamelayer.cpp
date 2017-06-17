#include "gamelayer.h"
#include "SimpleAudioEngine.h"
#include "Player_one.h"
#include "Player_se.h"
#include "Player_ai.h"
#include "TiledMap.h"
#include "cocos2d.h"
#include <math.h>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

bool gamelayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();
	allBombNum = 0;

	MenuItemLabel *menuItem = MenuItemLabel::create(Label::createWithSystemFont("FINISH ", "arial.ttf", 20), CC_CALLBACK_1(gamelayer::menucallback, this));
	menuItem->setTag(101);
	menuItem->setPosition(Vec2(760, 75));

	MenuItemLabel *menuItem_2 = MenuItemLabel::create(Label::createWithSystemFont("PLAY AGAIN", "arial.ttf", 20), CC_CALLBACK_1(gamelayer::menucallback, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(760, 25));

	auto menu = Menu::create(menuItem, menuItem_2, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	Sprite* gameFrame = Sprite::create("BG.png");
	gameFrame->setAnchorPoint(ccp(0, 0));
	addChild(gameFrame);
	return true;
};

void gamelayer::gamelayerInit() {

	loadMap();
	loadFigure();
	loadBar();
	addSwitch();
	schedule(schedule_selector(gamelayer::myUpdate), 0.2f);
}

void gamelayer::menucallback(Ref *psender)
{
	switch (((MenuItem *)psender)->getTag())
	{
	case 101:
	{
		tsm->gofinishscene();
	}
	break;
	case 102:
	{
		tsm->gochoosescene();
	}

	break;

	default:
		break;

	}
}

void gamelayer::loadMap() {
	myMap = TiledMap::createTiledMap(mapType);
	myMap->_map->setPosition(-20, 0);
	myMap->_map->setAnchorPoint(ccp(0, 0));
	addChild(myMap, 1);
}

void gamelayer::loadFigure() {
	Size winSize = Director::getInstance()->getWinSize();
	Point mapSize = Vec2(winSize.width *0.34, winSize.height*0.5);
	int figureNum = 0;
	for (int i = 0;i < playerOne;i++) {
		Player_one* player1 = Player_one::createFigureSprite(myMap->_figureOriginCoord[0], DOWN, USER, figureTeam[i], i);
		player1->myGamelayer = this;
		players.push_back(player1);
		myMap->_map->addChild(player1,2);
		figureNum++;
	}

	for (int i = 0;i < playerSe;i++) {
		Player_se* player2 = Player_se::createFigureSprite(myMap->_figureOriginCoord[1], DOWN, USER, figureTeam[figureNum], figureNum);
		player2->myGamelayer = this;
		players.push_back(player2);
		myMap->_map->addChild(player2, 2);
		figureNum++;
	}

	if (isClient) {

		teamInitForAi(figureNum);

		for (int i = 0;i < 4 - playerSe - playerOne;i++) {
			Player_ai* player_ai = Player_ai::createFigureSprite(myMap->_figureOriginCoord[3-i], DOWN, COMPUTER, figureTeam[figureNum], figureNum);
			player_ai->myGamelayer = this;
			players.push_back(player_ai);
			myMap->_map->addChild(player_ai, 1);
			figureNum++;
		}
	}

	for (auto& figure : players) {
		switch (figure->team) {
		case RED:
			red.push_back(figure);
			break;
		case GREEN:
			green.push_back(figure);
			break;
		case BLUE:
			blue.push_back(figure);
			break;
		case YELLOW:
			yellow.push_back(figure);
			break;
		default:
			break;
		}

		switch (figure->type)
		{
		case USER:
			user.push_back(figure);
			break;
		case COMPUTER:
			ai.push_back(figure);
			break;
		default:
			break;
		}
	}

}

void gamelayer::loadBar() {
	CountDownBar = countDownBar::createCountBar(FULL_TIME);
	addChild(CountDownBar,1);
}

void gamelayer::figureMove(int tag, int direction) {
	bool canMove = (!(myMap->isCollision(players[tag]->position,direction)))&&(!moveifBomb(tag,direction));//判断该人物朝该方向走是否会遇到障碍物
	players[tag]->Move(direction, (canMove&&moveifPlayer(tag)&&ksPlayer(tag)));//执行人物走动
	getTool(tag, players[tag]->position);//判断走到的位置是否有道具，有的话就捡起来
}
//forAi
bool gamelayer::ifMove(int tag, int direction) {
	bool canMove = (!(myMap->isCollision(players[tag]->position, direction))) && (!moveifBomb(tag, direction))&& moveifPlayer(tag);
	return canMove;
}

bool gamelayer::ifDanger(Point position) {
	for (auto* bomb : allBombs) {
		if (bomb->exit) {
			if ((bomb->bombRange[0].x - 20 < position.x&&bomb->bombRange[1].x + 20 > position.x&&fabsf(bomb->bombRange[0].y - position.y) < 20.0001) || (bomb->bombRange[2].y + 20 > position.y&&bomb->bombRange[3].y - 20 < position.y&&fabsf(bomb->bombRange[2].x - position.x) < 20.0001))
			{
				return true;
			}
		}
	}
	return false;
}


void gamelayer::putBomb(int playerTag, Point position) {
	Point mP = players[playerTag]->position;//将现在坐标转换为所在瓦片的中心坐标
	mP = myMap->tileCoordFromPosition(mP);
	mP = myMap->PositionFromTileCoord(mP);
	if(canBomb(mP)){
		int bombPower = players[playerTag]->bombPower;
		auto myBomb = Bomb::createBombSprite(mP, playerTag, bombPower, allBombNum, this);//创建并放炸弹
		++allBombNum;
		allBombs.push_back(myBomb);
		myMap->_map->addChild(myBomb, 1);
		SimpleAudioEngine::getInstance()->playEffect("effect1.wav");
		myBomb->bombDynamic();
		std::vector<Point> bombRange = myMap->calculateBomRangPoint(mP, bombPower);//计算炸弹所炸最远范围
		myBomb->initExplode(bombRange);//炸弹爆炸
	}
	

}

bool gamelayer::ksPlayer(int doerTag) {

	for (auto figures : players) //遍历所有玩家
	{
		if (figures != players[doerTag]) //与其他玩家进行碰撞检测
		{
			Point figP = figures->position;
			Point doP = players[doerTag]->position;
			if (fabsf(figP.x - doP.x) <= 10 && fabsf(figP.y - doP.y) <= 10) //碰撞
			{
				if (figures->state == STATE_BOXED) {
					if (figures->team != players[doerTag]->team) //是敌队
					{
						figures->Die(0.0);
						SimpleAudioEngine::getInstance()->playEffect("effect2.wav");
						++players[doerTag]->killNum;
						players[doerTag]->score += 666;
					}
					else {
						figures->BeSaved();
						SimpleAudioEngine::getInstance()->playEffect("effect7.wav");
						++players[doerTag]->saveNum;
						players[doerTag]->score += 233;
						
						}
					players[doerTag]->updateLabel();
					return true;
				}
			}
		}
	}
	return true;
}

bool gamelayer::moveifPlayer(int tag) {
	for (auto* figures : players) {
		if (tag != figures->tag) {
			switch (players[tag]->direction)
			{
			case LEFT:
			{
				if (fabsf(players[tag]->position.x - 25 - figures->position.x) < 8 && fabsf(players[tag]->position.y - figures->position.y) < 15)
				{
					return figures->state == STATE_BOXED ? true : false;
				}
				break;
			}
			case RIGHT:
			{
				if (fabsf(players[tag]->position.x + 25 - figures->position.x) < 8 && fabsf(players[tag]->position.y - figures->position.y) < 15)
				{
					return figures->state == STATE_BOXED ? true : false;
				}
				break;
			}
			case UP:
			{
				if (fabsf(players[tag]->position.y + 25 - figures->position.y) < 12 && fabsf(players[tag]->position.x - figures->position.x) < 15)
				{
					return figures->state == STATE_BOXED ? true : false;
				}
				break;
			}
			case DOWN:
			{
				if (fabsf(players[tag]->position.y - 25 - figures->position.y) < 12 && fabsf(players[tag]->position.x - figures->position.x) < 15)
				{
					return figures->state == STATE_BOXED ? true : false;
				}
				break;
			}
			default:
				break;
			}
		}
	}
	return true;
}


void gamelayer::bombifPlayer(std::vector<Point>&vec) {
	for (auto figures : players) {
		Point mP = figures->position;
		if (((mP.x < vec[1].x + 20) && (mP.x > vec[0].x - 20) && (mP.y < vec[1].y + 20) && (mP.y > vec[1].y - 20)) || ((mP.x < vec[2].x + 20) && (mP.x > vec[2].x - 20) && (mP.y < vec[2].y + 20) && (mP.y > vec[3].y - 20))) {
			figures->BeBoxed();
		}
	}
}

void gamelayer::getTool(int tag, Point position){
	int toolType = myMap->eatTool(position);
	if (toolType != 0&&toolType!=TOOL_BANANA&&toolType!=TOOL_STRAW) {
		players[tag]->CollectTool(toolType);
		SimpleAudioEngine::getInstance()->playEffect("effect5.wav");
	}
	if(toolType==TOOL_BANANA){
		timeLeft > 5.19 ? timeLeft -= 5 : timeLeft;
	}
	if (toolType == TOOL_STRAW)
	{
		timeLeft < 175 ? timeLeft += 5 : timeLeft;
	}
}


void gamelayer::myUpdate(float dt) {

	bool greenAllDie = true;
	bool redAllDie = true;
	bool blueAllDie = true;
	bool yellowAllDie = true;
	aiAllDie = true;
	bool userAllDie = true;
	//获得每队现状态 ai与玩家的状态
	for (auto& figure : players) {
		switch (figure->team)
		{
		case GREEN:
			greenAllDie = greenAllDie && (figure->state == STATE_DIED);
			break;
		case RED:
			redAllDie = redAllDie && (figure->state == STATE_DIED);
			break;
		case BLUE:
			blueAllDie = blueAllDie && (figure->state == STATE_DIED);
			break;
		case YELLOW:
			yellowAllDie = yellowAllDie && (figure->state == STATE_DIED);
			break;
		default:
			break;
		}

		switch (figure->type)
		{
		case USER:
			userAllDie = userAllDie&&figure->state == STATE_DIED;
			break;
		case COMPUTER:
			aiAllDie = aiAllDie&&figure->state == STATE_DIED;
			break;
		default:
			break;
		}
	}

	//时间到了,游戏结束
	if (timeLeft <= 0.19f) {
		unschedule(schedule_selector(gamelayer::myUpdate));
		for (auto&figure : players) {
			figure->stopAllSchedules();
		}
		if (isClient) {
			//客户端版：时间结束时，玩家没死算赢
			for (auto& figure : players) {
				if (figure->type == USER) {
					if (figure->state == STATE_FREE)
					{
						figure->Win();
					}
					winPlayers.push_back(figure);
				}
			}
		}
		else {
			//联网版：四组都有人活着或者四组都同时死去，则为平局；其他情况，有活着人物的队伍胜利，全死亡的队伍失败
			if (greenAllDie + redAllDie + blueAllDie + yellowAllDie != 4 && greenAllDie + redAllDie + blueAllDie + yellowAllDie != 0) {
				if (!greenAllDie) {
					for (auto& figure : green) {
						if (figure->state == STATE_FREE)
						{
							figure->Win();
						}
						winPlayers.push_back(figure);
					}
				}
				if (!redAllDie) {
					for (auto& figure : red) {
						if (figure->state == STATE_FREE)
						{
							figure->Win();
						}
						winPlayers.push_back(figure);
					}
				}
				if (!blueAllDie) {
					for (auto& figure : blue) {
						if (figure->state == STATE_FREE)
						{
							figure->Win();
						}
						winPlayers.push_back(figure);
					}
				}
				if (!yellowAllDie) {
					for (auto& figure : yellow) {
						if (figure->state == STATE_FREE)
						{
							figure->Win();
						}
						winPlayers.push_back(figure);
					}
				}
			}
			else {
				SimpleAudioEngine::getInstance()->playEffect("effect3.wav");
			}
		}
		scheduleOnce(schedule_selector(gamelayer::gameOver), 4.0f);  //展示得分的函数
		return;
	}

	//时间未到，但有人赢了,游戏结束
	if (timeLeft > 0) {
		timeLeft -= dt;
		CountDownBar->barUpdate(timeLeft, FULL_TIME);
		//客户端版：
		if (isClient) {
			//做出来ai的情况下：ai全死或者玩家全死或者都全死了游戏结束
			if (aiAllDie + userAllDie >= 1) {
				unschedule(schedule_selector(gamelayer::myUpdate));

				for (auto&figure : players) {
					figure->stopAllSchedules();
				}

				if (aiAllDie + userAllDie == 1) {//非平局
					if (aiAllDie) {
						for (auto& figure : user) {
							if (figure->state == STATE_FREE)
							{
								figure->Win();
							}
							winPlayers.push_back(figure);
						}
					}
					else {
						for (auto& figure : ai) {
							if (figure->state == STATE_FREE)
							{
								figure->Win();
							}
							winPlayers.push_back(figure);
						}
					}
				}
				else {
					isDraw = true;
				}
				scheduleOnce(schedule_selector(gamelayer::gameOver), 4.0f);  //展示得分的函数
				return;
			}


			////做成没有ai的：只剩一组队伍则胜利
			//if (greenAllDie + redAllDie + blueAllDie + yellowAllDie == 3) {
			//	unschedule(schedule_selector(gamelayer::myUpdate));
			//	if (!greenAllDie) {
			//		for (auto& figure : green) {
			//			if (figure->state == STATE_FREE)
			//{
			//	figure->Win();
			//}
			//			winPlayers.push_back(figure);
			//		}
			//	}
			//	if (!redAllDie) {
			//		for (auto& figure : red) {
			//			if (figure->state == STATE_FREE)
			//{
			//	figure->Win();
			//}
			//			winPlayers.push_back(figure);
			//		}
			//	}
			//	if (!blueAllDie) {
			//		for (auto& figure : blue) {
			//			if (figure->state == STATE_FREE)
			//{
			//	figure->Win();
			//}
			//			winPlayers.push_back(figure);
			//		}
			//	}
			//	if (!yellowAllDie) {
			//		for (auto& figure : yellow) {
			//			if (figure->state == STATE_FREE)
			//{
			//	figure->Win();
			//}
			//			winPlayers.push_back(figure);
			//		}
			//	}
			//	/*scheduleOnce(schedule_selector(), 1.0f);*/  //展示得分的函数
			//	return;
			//}
		}
		//联机版：
		if (!isClient) {//仅剩一组没死光算胜利
			if (playerOne != 1) {
				if (greenAllDie + redAllDie + blueAllDie + yellowAllDie >= 3) {
					unschedule(schedule_selector(gamelayer::myUpdate));
					for (auto&figure : players) {
						figure->stopAllSchedules();
					}
					if (greenAllDie + redAllDie + blueAllDie + yellowAllDie != 4) {
						if (!greenAllDie) {
							for (auto& figure : green) {
								if (figure->state == STATE_FREE)
								{
									figure->Win();
								}
								winPlayers.push_back(figure);
							}
						}
						if (!redAllDie) {
							for (auto& figure : red) {
								if (figure->state == STATE_FREE)
								{
									figure->Win();
								}
								winPlayers.push_back(figure);
							}
						}
						if (!blueAllDie) {
							for (auto& figure : blue) {
								if (figure->state == STATE_FREE)
								{
									figure->Win();
								}
								winPlayers.push_back(figure);
							}
						}
						if (!yellowAllDie) {
							for (auto& figure : yellow) {
								if (figure->state == STATE_FREE)
								{
									figure->Win();
								}
								winPlayers.push_back(figure);
							}
						}
					}
					else {
						isDraw = true;
					}
					
					scheduleOnce(schedule_selector(gamelayer::gameOver), 4.0f);  //展示得分的函数
					return;
				}
			}
		}
	}
}

void gamelayer::teamInitForAi(int figureNum) {
	if (playerSe + playerOne == 2)
	{
		if (figureTeam[0] + figureTeam[1] != 5)
		{
			figureTeam[figureNum] = 5 - figureTeam[0];
			figureTeam[figureNum + 1] = 5 - figureTeam[1];
		}
		else {
			if (figureTeam[0] == 1 || figureTeam[0] == 4) {
				figureTeam[figureNum] = 2;
				figureTeam[figureNum + 1] = 3;
			}
			else {
				figureTeam[figureNum] = 1;
				figureTeam[figureNum + 1] = 4;
			}
		}
	}
	else {
		figureTeam[figureNum] = 5 - figureTeam[0];
		if (figureTeam[0] == 1 || figureTeam[0] == 4) {
			figureTeam[figureNum + 1] = 2;
			figureTeam[figureNum + 2] = 3;
		}
		else {
			figureTeam[figureNum + 1] = 1;
			figureTeam[figureNum + 2] = 4;
		}
	}

}

void gamelayer::gameOver(float dt) {
	auto* label = LabelTTF::create("GAME_OVER", "Arial", 50);
	label->setPosition(Vec2(450, 550));
	addChild(label, 5);
	label->setFontFillColor(Color3B(240, 248, 255));
	if (!isDraw) {
		if (isClient&&aiAllDie) {
			auto* win = Sprite::create("win.png");
			win->setAnchorPoint(Vec2(0.5, 0.5));
			win->setPosition(Vec2(350, 300));
			win->setScale(0.8);
			myMap->_map->addChild(win, 3);
		}
		if (isClient && !aiAllDie) {
			auto* lose = Sprite::create("lose.png");
			lose->setAnchorPoint(Vec2(0.5, 0.5));
			lose->setPosition(Vec2(360, 300));
			lose->setScale(0.8);
			myMap->_map->addChild(lose, 3);
		}
		for (auto*figure : winPlayers) {
			figure->win = true;
		}
		for (auto*figure : players) {
			figure->gameover();
			if (figure->win) {
				auto* Win = LabelTTF::create("Win", "Arial", 15);
				Win->setAnchorPoint(Vec2(0.5, 0.5));
				Win->setFontFillColor(Color3B(240, 248, 255));
				Win->setPosition(Vec2(480, 320 - figure->tag * 50));
				addChild(Win, 4);
			}
			else {
				auto* Lose = LabelTTF::create("Lose", "Arial", 15);
				Lose->setAnchorPoint(Vec2(0.5, 0.5));
				Lose->setFontFillColor(Color3B(240, 248, 255));
				Lose->setPosition(Vec2(480, 320 - figure->tag * 50));
				addChild(Lose, 4);
			}
		}
	}
	else {
		auto* draw = Sprite::create("draw.png");
		draw->setAnchorPoint(Vec2(0.5, 0.5));
		draw->setPosition(Vec2(350, 300));
		draw->setScale(0.8);
		myMap->_map->addChild(draw, 3);

		for (auto* figure : players) {
			figure->gameover();
			auto* Draw = LabelTTF::create("Draw", "Arial", 15);
			Draw->setAnchorPoint(Vec2(0.5, 0.5));
			Draw->setFontFillColor(Color3B(240, 248, 255));
			Draw->setPosition(Vec2(480, 320 - figure->tag * 50));
			addChild(Draw, 4);
		}
	}
	scheduleOnce(schedule_selector(gamelayer::finishGame), 4.0f);

}
void gamelayer::finishGame(float dt) {

	unscheduleAllSelectors();
	tsm->gofinishscene();

}

bool gamelayer::moveifBomb(int tag, int direction) {

	for (auto* bomb : allBombs) {
		if (bomb->exit) {
			switch (direction) {
			case LEFT:
			{
				if (fabsf(players[tag]->position.x - 25 - bomb->position.x) < 8 && fabsf(players[tag]->position.y - bomb->position.y) < 15)
				{
					return true;
				}
				break;
			}
			case RIGHT:
			{
				if (fabsf(players[tag]->position.x + 25 - bomb->position.x) < 8 && fabsf(players[tag]->position.y - bomb->position.y) < 15)
				{
					return true;
				}
				break;
			}
			case UP:
			{
				if (fabsf(players[tag]->position.y + 25 - bomb->position.y) < 12 && fabsf(players[tag]->position.x - bomb->position.x) < 15)
				{
					return true;
				}
				break;
			}
			case DOWN:
			{
				if (fabsf(players[tag]->position.y - 25 - bomb->position.y) < 12 && fabsf(players[tag]->position.x - bomb->position.x) < 15)
				{
					return true;
				}
				break;
			}
			default:
				break;
			}
		}
		
	}
	return false;
}

int gamelayer::bombifBomb(std::vector<Point>&vec,int& theBombTag) {
	for (auto* bomb : allBombs) {
		if (bomb->exit) {
			if (((bomb->position.x<vec[1].x + 5) && (bomb->position.x>vec[0].x - 5) && (fabsf(bomb->position.y - vec[0].y) < 5)) || ((bomb->position.y<vec[2].y + 5) && (bomb->position.y>vec[3].y - 5) && (fabsf(bomb->position.x - vec[2].x) < 5)))
			{
				if (bomb->bombTag > theBombTag) {
					return BombOther;
				}
				else {
					return WaitBomb;
				}
			}
			else {
				return BombJust;
			}
		}
	}
	return BombJust;
}

void gamelayer::bombBomb(std::vector<Point>&vec, int& theBombTag) {
	for (auto* bomb : allBombs) {
		if (bomb->exit==true) {
			if (bomb->bombTag > theBombTag) {
				if (bomb->position.x<vec[1].x + 5 && bomb->position.x>vec[0].x - 5 && fabsf(bomb->position.y - vec[0].y) < 5)
				{
					bomb->bombExplode(0.0);
				}
				if (bomb->position.y<vec[2].y + 5 && bomb->position.y>vec[3].y - 5 && fabsf(bomb->position.x - vec[2].x) < 5)
				{
					bomb->bombExplode(0.0);
				}
			}
		}
	}
}

bool gamelayer::canBomb(Point mP) {
	for (auto* bomb : allBombs) {
		if (bomb->exit) {
			if (bomb->position == mP) {
				return false;
			}
		}
	}
	return true;
}

void gamelayer::onEnter() {
	Layer::onEnter();
}

void gamelayer::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("bg2.mp3", true);
	SimpleAudioEngine::getInstance()->playEffect("effect8.wav");
}

void gamelayer::onExit() {
	Layer::onExit();
}

void gamelayer::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
}

void gamelayer::cleanup() {
	Layer::cleanup();
}

void gamelayer::addSwitch() {
	auto* switchBG = Sprite::create("background.png");
	auto* switchOn = Sprite::create("on.png");
	auto* switchOff = Sprite::create("off.png");
	auto* switchBar = Sprite::create("button.png");
	auto* on = Label::create("on", "Arial", 15);
	auto* off = Label::create("pause", "Arial", 15);
	auto* controlSwitch = ControlSwitch::create(switchBG, switchOn, switchOff, switchBar, on, off);
	controlSwitch->setPosition(Vec2(80, 20));
	addChild(controlSwitch);
	controlSwitch->addTargetWithActionForControlEvents(this, cccontrol_selector(gamelayer::change), Control::EventType::VALUE_CHANGED);
}

void gamelayer::change(Object* pSender, Control::EventType event) {
	if (event == Control::EventType::VALUE_CHANGED) {
		auto* s = (ControlSwitch*)pSender;
		if (s->isOn()) {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}
		else {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		}
	}
}