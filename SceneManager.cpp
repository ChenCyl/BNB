#include "SceneManger.h"
#include "loadlayer.h"
#include "chooselayer.h"
#include "gamelayer.h"
#include "finishlayer.h"
void SceneManger::createloadscene()
{
	openscene = Scene::create();
	loadlayer *layer = loadlayer::create();
	layer->tsm = this;
	openscene->addChild(layer);
}
void SceneManger::gochoosescene()
{
	choosescene = Scene::create();
	chooselayer *layer = chooselayer::create();
	layer->tsm = this;
	choosescene->addChild(layer);

	Director::getInstance()->replaceScene(choosescene);



}
void SceneManger::gogamescene()
{
	gamescene = Scene::create();
	gamelayer *layer = gamelayer::create();
	layer->tsm = this;
	gamescene->addChild(layer);

	Director::getInstance()->replaceScene(gamescene);



}
void SceneManger::gofinishscene()
{
	finishscene = Scene::create();
	finishlayer *layer = finishlayer::create();
	layer->tsm = this;
	finishscene->addChild(layer);

	Director::getInstance()->replaceScene(finishscene);

}