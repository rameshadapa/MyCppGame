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
//bool HUDLayer::moveLeft 	= false;
//bool HUDLayer::moveRight	= false;
//bool HUDLayer::moveTop	= false;
//bool HUDLayer::moveBottom	= false;

bool HUDLayer::init()
{
    if(Layer::init())
    {
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(HUDLayer::onTouchesBegan, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HUDLayer::onTouchesEnded, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HUDLayer::onTouchesMoved, this);

   	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
    }
    return false;
}

void HUDLayer::onTouchesBegan(const vector<Touch*> &touches, Event *event)
{
    CCLOG("Multi touch began is calling.");
    for( auto &item: touches )
    {
	auto touch = item;
	auto location = touch->getLocation();
	CCLOG("Touch Location:: [%f %f]", location.x, location.y);
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
	s_map.erase(touch->getID());
    }
}

void HUDLayer::onTouchesCancelled(const vector<Touch*> &touches, Event *event)
{
    CCLOG("Multi touch cancelled is calling.");
    onTouchesEnded(touches, event);
}
