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
    Vec2 pos = _sprite->getPosition();
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.userData = this;

    _body = world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(_sprite->getContentSize().width*0.5f, _sprite->getContentSize().height*0.5f);

    b2FixtureDef charFixture;
    charFixture.shape = &shape;
    charFixture.density = 1.0f;
    charFixture.friction = 0.3f;

    _body->CreateFixture(&charFixture);
}

void GameObject::update(float delta)
{
    _sprite->update(delta);
}
