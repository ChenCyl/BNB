#pragma once
#pragma once
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class SceneManager
{
public:
	Scene  * openscene;
	Scene  * choosescene;
	Scene  * gamescene;
	Scene  * finishscene;
	Scene  * serverscene;
	Scene *clientScene;
	Scene *loadScene;


	void createloadscene();
	void gochoosescene(int chooseNum=1,bool isClient=true);
	void gogamescene(int &chooseNum, int &userOne, int &userTwo, int &map, Layer* theLayer,bool isClient);
	void gogamescene();
	void gofinishscene();
	void goserverscene();
	void goClientScene();
	void goLoadScene();


};
