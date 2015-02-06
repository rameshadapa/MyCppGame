#include "GameObject.h"

USING_NS_CC;

GameObject::GameObject(Sprite *sprite)
{
    _sprite = sprite;
}

GameObject::~GameObject()
{
    _body->GetWorld()->DestroyBody(_body);
}

void GameObject::setPhysics(b2World *world)
{
    b2BodyDef bodyDef;
    bodyDef.type = _bodyType;
    bodyDef.position.Set(getPosition().x, getPosition().y);
    bodyDef.userData = this;

    _body = world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(getContentSize().width*0.5f, getContentSize().height*0.5f);

    b2FixtureDef charFixture;
    charFixture.shape = &shape;
    charFixture.density = 1.0f;
    charFixture.friction = 0.3f;

    _body->CreateFixture(&charFixture);
}
