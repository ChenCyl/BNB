#pragma once
#pragma once
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class SceneManager
{
public:
	Scene  *openscene;
	Scene *choosescene;
	Scene  *gamescene;
	Scene  *finishscene;

	void createloadscene();
	void gochoosescene();
	void gogamescene();
	void gofinishscene();


};
