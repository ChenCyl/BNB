#ifndef _SWITCH_H_INCLUDED_
#define _SWITCH_H_INCLUDED_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Switch :public Layer
{
	public:
		int sceneType;
		int gameType;
		bool isGamelayer;


		static Switch* createSwitch(int sceneType, int gameType, bool isGamelayer);
		virtual bool init();
		CREATE_FUNC(Switch);
		void change(Object* pSender, Control::EventType event);
		void switchInit(int sceneType,int gameType,bool isGamelayer);
};
#endif // !_SWITCH_H_INCLUDED_