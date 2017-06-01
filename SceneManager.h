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


	void createloadscene();
	void gochoosescene();
	void gogamescene(int &figure,int &map);
	void gogamescene();
	void gofinishscene();
	void goserverscene();


};
