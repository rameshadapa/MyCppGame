#ifndef __GAME0BJECT_H__
#define __GAMEOBJECT_H__

#include <cocos2d.h>
#include <Box2D/Box2D.h>
#include "GameOSD.h"


class GameObject : public GameOSD
{
public:
    GameObject(cocos2d::Sprite* sprite);
    ~GameObject();

//    virtual bool init();
    void setBodyType(unsigned char type)	{ 	_bodyType = (b2BodyType)type;	}
    void setObjType(unsigned char type)		{	_objType = (ObjectType)type;	}
    void setPhysics(b2World *world);
    cocos2d::Vec2 getPosition()	{	return _position;	}
    void setPosition(const cocos2d::Vec2 &position)	
    {	
	_position = position;
    }
    cocos2d::Size getContentSize()	{	return _sprite->getContentSize();	}
    void update(float delta);

private:
    typedef enum {
    	OBJECT_DEFAULT = 0,
    	OBJECT_MC = OBJECT_DEFAULT,
    	OBJECT_LAYER_STATIC,
    	OBJECT_LAYER_DYNAMIC,
    }ObjectType;
    cocos2d::Sprite *_sprite;
    b2Body *_body;
    b2BodyType _bodyType;
    ObjectType _objType;
    cocos2d::Vec2 _position;
//    cocos2d::Vec2 _position;
};

#endif	// __GAMEOBJECT_H__
