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
bool HUDLayer::pressJump = false;
//bool HUDLayer::moveLeft 	= false;
//bool HUDLayer::moveRight	= false;
//bool HUDLayer::moveTop	= false;
//bool HUDLayer::moveBottom	= false;

bool HUDLayer::init()
{
    if(Layer::init())
    {
        Size size = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(HUDLayer::onTouchesBegan, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HUDLayer::onTouchesEnded, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HUDLayer::onTouchesMoved, this);

   	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    	mask = ShaderNode::shaderNodeWithVertex("", "game.glsl");
    	mask->setPosition(Vec2(size.width/2.0f, size.height/2.0f));
	mask->isLightMask(true);
    	this->addChild(mask, 0);

 	leftButton = Sprite::create("joystick.png");
				//		"joystick.png", CC_CALLBACK_1(HUDLayer::leftPress, this));
	leftButton->setPosition(Point(origin.x+leftButton->getContentSize().width, origin.y + leftButton->getContentSize().height));

	rightButton = Sprite::create("joystick.png");	//, "joystick.png", CC_CALLBACK_1(HUDLayer::rightPress, this));
	rightButton->setPosition(Point(leftButton->getPosition().x + leftButton->getContentSize().width, leftButton->getPosition().y));

	jumpButton = Sprite::create("joystick.png");
	jumpButton->setPosition(Point(origin.x+size.width-jumpButton->getContentSize().width/2.0f, origin.y + jumpButton->getContentSize().height*3.0f/2.0f));
	
/*	auto menu = Menu::create(leftButton, NULL);
	menu->setPosition(Point::ZERO);
	menu->addChild(rightButton);
*/
	this->addChild(leftButton, 1);
	this->addChild(rightButton, 1);
	this->addChild(jumpButton, 1);

	return true;
    }
    return false;
}

void HUDLayer::update(float delta)
{
//    mask->setLightPos(Vec2(gameChar->getPosition().x, gameChar->getPosition().y));
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
	    HUDLayer::moveLeft = true;
	}
	if(location.x>(rightButton->getPosition().x - rightButton->getContentSize().width/2.0f)
		 && location.x<(rightButton->getPosition().x + rightButton->getContentSize().width/2.0f)
		 && location.y>(rightButton->getPosition().y - rightButton->getContentSize().height/2.0f)
		 && location.y<(rightButton->getPosition().y + rightButton->getContentSize().height/2.0f))
	{
	    HUDLayer::moveRight = true;
	}
	if(location.x>(jumpButton->getPosition().x - jumpButton->getContentSize().width/2.0f)
		 && location.x<(jumpButton->getPosition().x + jumpButton->getContentSize().width/2.0f)
		 && location.y>(jumpButton->getPosition().y - jumpButton->getContentSize().height/2.0f)
		 && location.y<(jumpButton->getPosition().y + jumpButton->getContentSize().height/2.0f))
	{
	    HUDLayer::pressJump = true;
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
	if(location.x>(leftButton->getPosition().x - leftButton->getContentSize().width/2.0f)
		 && location.x<(leftButton->getPosition().x + leftButton->getContentSize().width/2.0f)
		 && location.y>(leftButton->getPosition().y - leftButton->getContentSize().height/2.0f)
		 && location.y<(leftButton->getPosition().y + leftButton->getContentSize().height/2.0f))
	{
	    HUDLayer::moveLeft = true;
	}
	else
	{
	    HUDLayer::moveLeft = false;
	}
	if(location.x>(rightButton->getPosition().x - rightButton->getContentSize().width/2.0f)
		 && location.x<(rightButton->getPosition().x + rightButton->getContentSize().width/2.0f)
		 && location.y>(rightButton->getPosition().y - rightButton->getContentSize().height/2.0f)
		 && location.y<(rightButton->getPosition().y + rightButton->getContentSize().height/2.0f))
	{
	    HUDLayer::moveRight = true;
	}
	else
	{
	    HUDLayer::moveRight = false;
	}
	if(location.x>(jumpButton->getPosition().x - jumpButton->getContentSize().width/2.0f)
		 && location.x<(jumpButton->getPosition().x + jumpButton->getContentSize().width/2.0f)
		 && location.y>(jumpButton->getPosition().y - jumpButton->getContentSize().height/2.0f)
		 && location.y<(jumpButton->getPosition().y + jumpButton->getContentSize().height/2.0f))
	{
	    HUDLayer::pressJump = true;
	}
	else
	{
	    HUDLayer::pressJump = false;
	}
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
	HUDLayer::moveLeft = false;
	HUDLayer::moveRight = false;
	HUDLayer::pressJump = false;
	s_map.erase(touch->getID());
    }
}

void HUDLayer::onTouchesCancelled(const vector<Touch*> &touches, Event *event)
{
    CCLOG("Multi touch cancelled is calling.");
    onTouchesEnded(touches, event);
}
