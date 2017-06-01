#include "SceneManager.h"
#include "loadlayer.h"
#include "chooselayer.h"
#include "gamelayer.h"
#include "finishlayer.h"
#include "serverlayer.h"
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
void SceneManager::gochoosescene()
{
	choosescene = Scene::create();
	chooselayer *layer = chooselayer::create();
	layer->tsm = this;
	choosescene->addChild(layer);

	Director::getInstance()->replaceScene(choosescene);



}
void SceneManager::gogamescene()
{
	gamescene = Scene::create();
	gamelayer *layer = gamelayer::create();
	layer->tsm = this;
	gamescene->addChild(layer);

	Director::getInstance()->replaceScene(gamescene);



}
void SceneManager::gogamescene(int &figure ,int &map)
{
	gamescene = Scene::create();
	gamelayer *layer = gamelayer::create();
	layer->tsm = this;
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
