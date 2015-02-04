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
    if(HUDLayer::moveRight)
    {
	charBody->SetTransform(b2Vec2(-GRAVITY_IN_PIXELS/2.0f, 0.0f), CC_DEGREES_TO_RADIANS(0));
//	charBody->SetLinearVelocity(b2Vec2(-GRAVITY_IN_PIXELS/2.0f, 0.0f));
    }
    if(HUDLayer::moveLeft)
    {
	charBody->SetTransform(b2Vec2(GRAVITY_IN_PIXELS/2.0f, 0.0f), CC_DEGREES_TO_RADIANS(0));
//	charBody->SetLinearVelocity(b2Vec2(GRAVITY_IN_PIXELS/2.0f, 0.0f));
    }
    if(HUDLayer::pressJump)
    {
	charBody->SetTransform(b2Vec2(0.0f, -GRAVITY_IN_PIXELS), CC_DEGREES_TO_RADIANS(0));
//	charBody->SetLinearVelocity(b2Vec2(0.0f, -GRAVITY_IN_PIXELS));
    }
    b2Vec2 position = charBody->GetPosition();
    this->setPosition(position.x, position.y);
}
