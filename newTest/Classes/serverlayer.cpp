#include "network/SocketIO.h"
#include "serverlayer.h"
#include "cocos2d.h"
#include "string"

USING_NS_CC;
using namespace cocos2d;


bool Client::init()
{


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	/*MenuItemLabel *menuItem = MenuItemLabel::create(Label::createWithSystemFont("continue", "", 30), CC_CALLBACK_1(client::menucallback, this));
	menuItem->setColor(Color3B(0, 0, 0));
	menuItem->setTag(101);
	menuItem->setPosition(Vec2(winSize.width *0.8, winSize.height*0.2));

	auto menu = Menu::create(menuItem,  NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);*/

	auto pItemLabel1 = Label::createWithTTF("send massage", "fonts/Marker Felt.ttf", 24);
	/*pItemLabel1->setPosition(Vec2(winSize.width *0.8, winSize.height*0.2));
	this->addChild(pItemLabel1, 1);*/

	auto pItemMenu1 = MenuItemLabel::create(pItemLabel1, CC_CALLBACK_1(Client::menuSendMsgCallback, this));

	Menu *mn = Menu::create(pItemMenu1, nullptr);
	mn->alignItemsVertically();
	this->addChild(mn);

	label = Label::createWithTTF("helloworld", "fonts/Marker Felt.ttf", 26);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	_sioClient = cocos2d::network::SocketIO::connect("http://localhost:3000/", *this);//连接服务器
	_sioClient->setTag("Cocos2d-x Client1");
	//event callclientevent
	_sioClient->on("callClientEvent", CC_CALLBACK_2(Client::callClientEvent, this));
	return true;

}
void Client::menuSendMsgCallback(Ref*pSender)
{
	if (_sioClient != nullptr)
		_sioClient->send("Hello Socket.IO");
	if (_sioClient != nullptr)
		_sioClient->emit("callServerEvent", "{\"message\":\"HelloServer.\"}");
}

void Client::onConnect(cocos2d::network::SIOClient *client)
{
	log("Client::onConnect called");
	__String *s = __String::createWithFormat("%s connected!", client->getTag());
	label->setString(s->getCString());
}
void Client::onMessage(cocos2d::network::SIOClient *client, const std::string&data)
{
	log("Client::onMessage received:%s", data.c_str());
	__String *s = __String::createWithFormat("%s received message.", client->getTag());
	label->setString(s->getCString());
}
void Client::onClose(cocos2d::network::SIOClient *client)
{
	log("Client::onClose called");
	__String *s = __String::createWithFormat("%s closed!", client->getTag());
	label->setString(s->getCString());

	if (client == _sioClient)
	{
		_sioClient = nullptr;
	}
}
void Client::onError(cocos2d::network::SIOClient *client, const std::string&data)
{
	log("Client::onError received:%s", data.c_str());
	__String *s = __String::createWithFormat("%s  received error.", client->getTag());
	label->setString(s->getCString());
}
void Client::callClientEvent(cocos2d::network::SIOClient *client, const std::string&data)
{
	log("Client::callClientEvent received:%s", data.c_str());
	__String*s = __String::createWithFormat("%s Server CallBack", client->getTag());
	label->setString(s->getCString());
}


void Client::menucallback(Ref *psender)
{
	switch (((MenuItem *)psender)->getTag())
	{
	case 101:
	{
		tsm->gochoosescene();
	}
	default:
		break;


	}

}
