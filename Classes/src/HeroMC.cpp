#include "HeroMC.h"
#include "HUDLayer.h"

USING_NS_CC;

HeroMC::HeroMC(void)
{
//   heroSkeleton = SkeletonAnimation::createWithFile("mc/hero.json", "mc/hero.atlas", 0.5f);
//   heroSkeleton->setScale(1.0);
    setType(CHAR_TYPE_MC);
}

HeroMC::~HeroMC()
{
//    TO DO.
//    delete heroSkeleton;
}

HeroMC* HeroMC::create(const std::string& fileName)
{
    HeroMC *character = new HeroMC();
    if(character && character->initWithFile(fileName))
    {
	character->autorelease();
	return character;
    } 
    CC_SAFE_DELETE(character);
    return NULL;
}


void HeroMC::update(float delta)
{
    if(true)
    {
	if(HUDLayer::moveRight)
	{
	Vec2 velocity = Vec2(-GRAVITY_IN_PIXELS/2.0f, 0.0f);
	Move(velocity);
	}
	if(HUDLayer::moveLeft)
	{
	Vec2 velocity = Vec2(GRAVITY_IN_PIXELS/2.0f, 0.0f);
	Move(velocity);
	}
	if(HUDLayer::pressJump)
	{
	Vec2 velocity = Vec2(0.0f, -GRAVITY_IN_PIXELS);
	Move(velocity);
	}
	if(HUDLayer::pressMine)
	{
		CCLog("Started mining....");
	}

	b2Vec2 position = charBody->GetPosition();
	this->setPosition(position.x, position.y);
    }
}
