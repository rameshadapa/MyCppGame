#include "HeroMC.h"

USING_NS_CC;

HeroMC* HeroMC::instance = nullptr;

HeroMC::HeroMC(void)
{

   heroSkeleton = SkeletonAnimation::createWithFile("mc/hero.json", "mc/hero.atlas", 0.5f);
   heroSkeleton->setScale(1.0);

}

HeroMC::~HeroMC()
{
//    TO DO.
    delete heroSkeleton;
}

HeroMC* HeroMC::HeroInstance()
{
    if(!instance)
    {
	instance = new HeroMC();
    } 

    return instance;
}

void HeroMC::Move(float delta)
{
    if(_direction == LEFT)
    {
    	heroSkeleton->setAnimation(0, "walk_left", false);
    }
    else if(_direction == RIGHT)
    {
	heroSkeleton->setAnimation(0, "walk_right", false);
    }
    this->SetPosition(GetPosition() + _velocity*delta);
}

void HeroMC::Jump(float delta)
{
    if(_direction == LEFT)
    {
	heroSkeleton->setAnimation(0, "jump_left", false);
    }
    else
    {
	heroSkeleton->setAnimation(0, "jump_right", false);
    }
    this->SetPosition(GetPosition() + _velocity*delta);
}

void HeroMC::SetDirection(unsigned char direction)	{
    if(_direction != direction)
    {
	if(_direction == LEFT)
	{
	    heroSkeleton->setAnimation(0, "left_to_right", false);
	}
	else if(_direction == RIGHT)
	{
	    heroSkeleton->setAnimation(0, "right_to_left", false);
	}
	_direction = direction;
    }
}

void HeroMC::SetMineDirection(unsigned char mineDirection)
{
    if(mineDirection == MINE_SIDE)
    {
	if(_direction == LEFT)
	{
	    heroSkeleton->setAnimation(0, "mine_left_side", false);
	}
	else if(_direction == RIGHT)
	{
	    heroSkeleton->setAnimation(0, "mine_right_side", false);
	}
    }
    else if(mineDirection == MINE_DOWN)
    {
	if(_direction == LEFT)
	{
	    heroSkeleton->setAnimation(0, "mine_left_down", false);
	}
	else if(_direction == RIGHT)
	{
	    heroSkeleton->setAnimation(0, "mine_right_down", false);
	}
    }
    _mineDirection = mineDirection;
}
