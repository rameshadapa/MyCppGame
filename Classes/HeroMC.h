#ifndef __HERO_MC__
#define __HERO_MC__

#include "cocos2d.h"
#include "GameOSD.h"
#include "Box2D/Box2D.h"
#include <spine/spine-cocos2dx.h>

class HeroMC : public cocos2d::Sprite, public GameOSD
{
    enum
    {
	LEFT,
	RIGHT,
    }_direction;

    enum
    {
	MINE_SIDE,
	MINE_BOTTOM
    }_mineDireciton;

    spine::SkeletonAnimation* heroSkeleton;
    cocos2d::Vec2 _velocity;
    cocos2d::Vec2 _position;

    Sprite *mainChar;

public:
    HeroMC(void);
    ~HeroMC(void);

    void Move(float delta);
    void Jump(float delta);

    void SetDirection(unsigned char direction);
    unsigned char GetDirection()	{	return _direction;	}

    void SetVelocity(cocos2d::Vec2 velocity)	{	_velocity = velocity;	}
    cocos2d::Vec2 getVelocity()	{	return _velocity;	}

    void SetPosition(cocos2d::Vec2 position)	{	_position = position;	}
    cocos2d::Vec2 GetPosition()	{	return _position;	}

    void SetMineDirection(unsigned char mineDirection);
//    unsigned char GetMineDirection()	{	return _mineDirection;	}

    static HeroMC* create(const std::string& fileName);

    void SetPhysics(b2World *world);

    void update(float delta);
};

#endif	// __HERO_MC__
