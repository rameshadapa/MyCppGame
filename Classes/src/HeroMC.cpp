#include "HeroMC.h"
#include "HUDLayer.h"

USING_NS_CC;

HeroMC::HeroMC(void)
{
//   heroSkeleton = SkeletonAnimation::createWithFile("mc/hero.json", "mc/hero.atlas", 0.5f);
//   heroSkeleton->setScale(1.0);

}

HeroMC::~HeroMC()
{
//    TO DO.
//    delete heroSkeleton;
}



void HeroMC::update(float delta)
{
    Vec2 velocity = Vec2(0.0f, 0.0f);
    if(HUDLayer::moveRight)
    {
	velocity = Vec2(-GRAVITY_IN_PIXELS/2.0f, 0.0f);
//	charBody->SetLinearVelocity(b2Vec2(-GRAVITY_IN_PIXELS/2.0f, 0.0f));
    }
    if(HUDLayer::moveLeft)
    {
	velocity = Vec2(GRAVITY_IN_PIXELS/2.0f, 0.0f);
//	charBody->SetLinearVelocity(b2Vec2(GRAVITY_IN_PIXELS/2.0f, 0.0f));
    }
    if(HUDLayer::pressJump)
    {
	velocity = Vec2(0.0f, -GRAVITY_IN_PIXELS);
//	charBody->SetLinearVelocity(b2Vec2(0.0f, -GRAVITY_IN_PIXELS));
    }

//    if(
}
