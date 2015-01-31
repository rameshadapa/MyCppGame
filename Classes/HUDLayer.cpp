#include "HUDLayer.h"

USING_NS_CC;
using namespace std;

class TouchPoint : public Node
{
    Vec2 touchPoint;
    public:
	TouchPoint(const Vec2 &touchPoint)
	{
	    this->touchPoint = touchPoint;
	}
	static TouchPoint* touchPointWithArea(const Vec2 &touchPoint)
	{
	    auto pRet = new (std::nothrow)TouchPoint(touchPoint);
	    return pRet;
	}
};

static Map<int, TouchPoint*> s_map;
bool HUDLayer::moveLeft = false;
bool HUDLayer::moveRight = false;
//bool HUDLayer::moveLeft 	= false;
//bool HUDLayer::moveRight	= false;
//bool HUDLayer::moveTop	= false;
//bool HUDLayer::moveBottom	= false;
/*
Scene* HUDLayer::createScene()
{
    auto scene = Scene::create();

    auto layer = HUDLayer::create();

    scene->addChild(layer);
    return scene;
}
*/
bool HUDLayer::init()
{
    if(Layer::init())
    {
        Point origin = Director::getInstance()->getVisibleOrigin();
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(HUDLayer::onTouchesBegan, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HUDLayer::onTouchesEnded, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HUDLayer::onTouchesMoved, this);

   	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

 	leftButton = Sprite::create("joystick.png");
				//		"joystick.png", CC_CALLBACK_1(HUDLayer::leftPress, this));
	leftButton->setPosition(Point(origin.x+leftButton->getContentSize().width, origin.y + leftButton->getContentSize().height));

	rightButton = Sprite::create("joystick.png");	//, "joystick.png", CC_CALLBACK_1(HUDLayer::rightPress, this));
	rightButton->setPosition(Point(leftButton->getPosition().x + leftButton->getContentSize().width, leftButton->getPosition().y));
	
/*	auto menu = Menu::create(leftButton, NULL);
	menu->setPosition(Point::ZERO);
	menu->addChild(rightButton);
*/
	this->addChild(leftButton, 1);
	this->addChild(rightButton, 1);
	return true;
    }
    return false;
}

void HUDLayer::leftPress(Ref *sender)
{
	CCLOG("Pressing left button..");
}

void HUDLayer::rightPress(Ref *sender)
{
	CCLOG("Pressing right button...");
}

void HUDLayer::onTouchesBegan(const vector<Touch*> &touches, Event *event)
{
    CCLOG("Multi touch began is calling.");
    for( auto &item: touches )
    {
	auto touch = item;
	auto location = touch->getLocation();
	CCLog("Touch Location:: [%f %f]", location.x, location.y);
	if(location.x>(leftButton->getPosition().x - leftButton->getContentSize().width/2.0f)
		 && location.x<(leftButton->getPosition().x + leftButton->getContentSize().width/2.0f)
		 && location.y>(leftButton->getPosition().y - leftButton->getContentSize().height/2.0f)
		 && location.y<(leftButton->getPosition().y + leftButton->getContentSize().height/2.0f))
	{
	    HUDLayer::moveRight = true;
	}
	auto touchPoint = TouchPoint::touchPointWithArea(location);
	s_map.insert(touch->getID(), touchPoint);
    }
}

void HUDLayer::onTouchesMoved(const vector<Touch*> &touches, Event *event)
{
    CCLOG("Multi touch moved is calling.");
    for( auto &item: touches )
    {
	auto touch = item;
	auto location = touch->getLocation();
	auto touchPoint = TouchPoint::touchPointWithArea(location);
	s_map.erase(touch->getID());
	s_map.insert(touch->getID(), touchPoint);
    }
}

void HUDLayer::onTouchesEnded(const vector<Touch*> &touches, Event *event)
{
    CCLOG("Multi touch ended is calling.");
    for( auto &item: touches )
    {
	auto touch = item;
	auto location = touch->getLocation();
	if(location.x>(leftButton->getPosition().x - leftButton->getContentSize().width/2.0f)
		 && location.x<(leftButton->getPosition().x + leftButton->getContentSize().width/2.0f)
		 && location.y>(leftButton->getPosition().y - leftButton->getContentSize().height/2.0f)
		 && location.y<(leftButton->getPosition().y + leftButton->getContentSize().height/2.0f))
	{
	    HUDLayer::moveRight = false;
	}
	s_map.erase(touch->getID());
    }
}

void HUDLayer::onTouchesCancelled(const vector<Touch*> &touches, Event *event)
{
    CCLOG("Multi touch cancelled is calling.");
    onTouchesEnded(touches, event);
}
