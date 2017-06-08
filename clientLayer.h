#ifndef _CLIENTLAYER_H_INCLUDED_
#define _CLIENTLAYER_H_INCLUDED_

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
USING_NS_CC;
class clientLayer:public Layer
{
public:
	CREATE_FUNC(clientLayer);
	virtual bool init();
	void menucallback(Ref *psender);

public:
	SceneManager *tsm;
};

#endif // !_CLIENTLAYER_H_INCLUDED_