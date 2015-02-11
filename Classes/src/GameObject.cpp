#include "GameObject.h"

USING_NS_CC;

GameObject::GameObject(Sprite *sprite)
{
    _sprite = sprite;
}

GameObject::~GameObject()
{
    _body->DestroyFixture(_charFixture);
    _body->GetWorld()->DestroyBody(_body);
}

void GameObject::setPhysics(b2World *world)
{
    b2BodyDef bodyDef;
    bodyDef.type = _bodyType;
    Vec2 pos = getPosition();
    bodyDef.position.Set(pos.x, pos.y);
    CCLog("Object Position:: [%f  %f]", pos.x, pos.y);
    bodyDef.userData = this;

    _body = world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(_sprite->getContentSize().width*0.5f, _sprite->getContentSize().height*0.5f);

    _charFixture->shape = &shape;
    _charFixture->density = 1.0f;
    _charFixture->friction = 0.3f;

    _body->CreateFixture(_charFixture);
}

void GameObject::update(float delta)
{
    _sprite->update(delta);
}
