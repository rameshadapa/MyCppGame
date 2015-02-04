#include "GameCharacter.h"

USING_NS_CC;

GameCharacter::GameCharacter()
{
}

GameCharacter::~GameCharacter()
{
}

GameCharacter* GameCharacter::create(const std::string& fileName)
{
    GameCharacter *character = new GameCharacter();
    if(character && character->initWithFile(fileName))
    {
	character->autorelease();
	return character;
    } 
    CC_SAFE_DELETE(character);
    return NULL;
}


void GameCharacter::setPhysics(b2World *world)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(getPosition().x, getPosition().y);
    bodyDef.userData = this;

    charBody = world->CreateBody(&bodyDef);
    b2PolygonShape charShape;
    charShape.SetAsBox(getContentSize().width*0.5f, getContentSize().height*0.5f);

    b2FixtureDef charFixture;
    charFixture.shape = &charShape;
    charFixture.density = 1.0f;
    charFixture.friction = 0.3f;

    charBody->CreateFixture(&charFixture);
}

void GameCharacter::Move(Vec2 velocity)
{
    charBody->SetTransform(b2Vec2(velocity.x, velocity.y), CC_DEGREES_TO_RADIANS(0));
    b2Vec2 position = charBody->GetPosition();
    this->setPosition(position.x, position.y);
}

void GameCharacter::Jump(Vec2 jumpVelocity)
{
}
