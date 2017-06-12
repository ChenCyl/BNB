#include "SceneManager.h"
#include "loadlayer.h"
#include "chooselayer.h"
#include "gamelayer.h"
#include "finishlayer.h"
#include "serverlayer.h"
#include "clientLayer.h"

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
void SceneManager::createloadscene()
{
	openscene = Scene::create();
	loadlayer *layer = loadlayer::create();
	layer->tsm = this;
	openscene->addChild(layer);
}
void SceneManager::gochoosescene(int chooseNum,bool isClient)
{
	choosescene = Scene::create();
	chooselayer *layer = chooselayer::create();
	layer->tsm = this;
	layer->chooseNum = chooseNum;
	layer->isClient = isClient;
	layer->chooselayerInit();
	choosescene->addChild(layer);
	
	Director::getInstance()->pushScene(choosescene);

}
void SceneManager::gogamescene()
{
	gamescene = Scene::create();
	gamelayer *layer = gamelayer::create();
	layer->tsm = this;
	gamescene->addChild(layer);

	Director::getInstance()->replaceScene(gamescene);

}
void SceneManager::goLoadScene() {
	loadScene = Scene::create();
	loadlayer *layer = loadlayer::create();
	layer->tsm = this;
	loadScene->addChild(layer);

	Director::getInstance()->replaceScene(loadScene);
}
void SceneManager::gogamescene(int &chooseNum, int &userOne, int &userTwo, int &map,Layer* theLayer,bool isClient)
{
	gamescene = Scene::create();
	gamelayer *layer = gamelayer::create();
	layer->tsm = this;
	layer->isClient = isClient;
	if (chooseNum == 2) {
		layer->playerOne = 1;layer->playerSe = 1;/*layer->playerAi = 2;*/
		layer->figureTeam[0] = userOne;
		layer->figureTeam[1] = userTwo;
	}else {
		layer->figureTeam[0] = userOne;
	}
	layer->gamelayerInit();
	gamescene->addChild(layer);

	Director::getInstance()->replaceScene(gamescene);



}
void SceneManager::gofinishscene()
{
	finishscene = Scene::create();
	finishlayer *layer = finishlayer::create();
	layer->tsm = this;
	finishscene->addChild(layer);

	Director::getInstance()->replaceScene(finishscene);

}
void SceneManager::goserverscene()
{
	serverscene = Scene::create();
	serverlayer *layer = serverlayer::create();
	layer->tsm = this;
	serverscene->addChild(layer);

	Director::getInstance()->replaceScene(serverscene);

}
void SceneManager::goClientScene() {
	clientScene = Scene::create();
	clientLayer *layer = clientLayer::create();
	layer->tsm = this;
	clientScene->addChild(layer);

	Director::getInstance()->replaceScene(clientScene);

}