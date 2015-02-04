#ifndef __GAME_CHARACTER_H__
#define __GAME_CHARACTER_H__

#include <cocos2d.h>
#include "GameOSD.h"
#include "Box2D/Box2D.h"
#include <spine/spine-cocos2dx.h>

enum
{
    CHAR_TYPE_DEFAULT,
    CHAR_TYPE_MC = CHAR_TYPE_DEFAULT,
};

class GameCharacter : public cocos2d::Sprite, public GameOSD
{
public:
    GameCharacter();
    virtual ~GameCharacter();

    static GameCharacter* create(const std::string& fileName);

    void setPhysics(b2World* world);

//    void setDefaultVelocity(cocos2d::Vec2 velocity)	{  	_velocity = velocity;	}
    void setDefaultPosition(cocos2d::Vec2 position)	{	_position = position;	}

    void Move(cocos2d::Vec2 velocity);
    void Jump(cocos2d::Vec2 jumpVelocity);

    void setType(int type)	{	type = charType;	}
    int getType()	{	return charType;	}

private:

    spine::SkeletonAnimation* charSkeleton;
//    cocos2d::Vec2 _velocity;
//    cocos2d::Vec2 _position;

protected:
    b2Body 	*charBody;
    int 	charType;
};

#endif 	// __GAME_CHARACTER_H__
