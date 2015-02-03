#include "HeroMC.h"
#include "HUDLayer.h"

USING_NS_CC;

HeroMC::HeroMC(void)
{
    _velocity = Vec2(0,0);
//   heroSkeleton = SkeletonAnimation::createWithFile("mc/hero.json", "mc/hero.atlas", 0.5f);
//   heroSkeleton->setScale(1.0);

}

HeroMC::~HeroMC()
{
//    TO DO.
//    delete heroSkeleton;
}

HeroMC* HeroMC::create(const std::string& fileName)
{
    HeroMC *gameMC = new HeroMC();
    if(gameMC && gameMC->initWithFile(fileName))
    {
	gameMC->autorelease();
	return gameMC;
    } 
    CC_SAFE_DELETE(gameMC);
    return NULL;
}

void HeroMC::SetPhysics(b2World *world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(getPosition().x, getPosition().y);
      	bodyDef.userData = this;

	mcBody = world->CreateBody(&bodyDef);
	b2PolygonShape mcShape;
	mcShape.SetAsBox(getContentSize().width*0.5f, getContentSize().height*0.5f);

	b2FixtureDef mcFixture;
	mcFixture.shape = &mcShape;
	mcFixture.density = 1.0f;
	mcFixture.friction = 0.3f;

	mcBody->CreateFixture(&mcFixture);

//	setB2Body(mcBody);
//	super->setPTMRatio(32.0);
}

void HeroMC::Move(float delta)
{
/*    if(_direction == LEFT)
    {
    	heroSkeleton->setAnimation(0, "walk_left", false);
    }
    else if(_direction == RIGHT)
    {
	heroSkeleton->setAnimation(0, "walk_right", false);
    }*/
    this->SetPosition(GetPosition() + _velocity*delta);
}

void HeroMC::Jump(float delta)
{
/*    if(_direction == LEFT)
    {
	heroSkeleton->setAnimation(0, "jump_left", false);
    }
    else
    {
	heroSkeleton->setAnimation(0, "jump_right", false);
    }*/
    this->SetPosition(GetPosition() + _velocity*delta);
}

void HeroMC::SetDirection(unsigned char direction)	{
/*    if(_direction != direction)
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
    }*/
}

void HeroMC::SetMineDirection(unsigned char mineDirection)
{
/*    if(mineDirection == MINE_SIDE)
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
    _mineDirection = mineDirection;*/
}

void HeroMC::update(float delta)
{
/*    Point gravity = Point(0.0, GRAVITY_IN_PIXELS);
    Point gravityStep = gravity * delta;

    _velocity = _velocity + gravityStep;
    Point velocityStep = _velocity * delta;
*/
    if(HUDLayer::moveRight)
    {
	mcBody->SetLinearVelocity(b2Vec2(-GRAVITY_IN_PIXELS/2.0f, 0.0f));
    }
    if(HUDLayer::moveLeft)
    {
	mcBody->SetLinearVelocity(b2Vec2(GRAVITY_IN_PIXELS/2.0f, 0.0f));
    }
    if(HUDLayer::pressJump)
    {
	mcBody->SetLinearVelocity(b2Vec2(0.0f, -GRAVITY_IN_PIXELS));
    }
    b2Vec2 position = mcBody->GetPosition();
    this->setPosition(position.x, position.y);
//    CCLog("Velocity [%f, %f]   Position [%f, %f]", _velocity.x, _velocity.y, _position.x, _position.y);
}
