#include "network/SocketIO.h"
#include "cocos2d.h"
#include "SceneManager.h"
#include "network\WebSocket.h"


USING_NS_CC;

class Client :public cocos2d::Layer
	, public cocos2d::network::SocketIO::SIODelegate
{
	cocos2d::network::SIOClient *_sioClient;
	cocos2d::Label *label;
public:
	static cocos2d::Scene *createScene();
	virtual bool init();

	void menuSendMsgCallback(cocos2d::Ref *pSender);

	CREATE_FUNC(Client);

	void menucallback(Ref *psender);
	SceneManager *tsm;

	virtual void onConnect(cocos2d::network::SIOClient *client);
	virtual void onMessage(cocos2d::network::SIOClient *client, const std::string&data);
	virtual void onClose(cocos2d::network::SIOClient *client);
	virtual void onError(cocos2d::network::SIOClient *client, const std::string&data);

	void callClientEvent(cocos2d::network::SIOClient *client, const std::string&data);

};
