#include "GamePlayScene.h"
#include "GameOSD.h"
#include "ShaderLayer.h"
#include "ShaderNode.h"
#include "HeroMC.h"
#include "TiledBodyCreator.h"

USING_NS_CC;

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
    delete _world;
}

Scene* GamePlay::createScene()
{
    auto scene = Scene::create();
  
    auto layer = GamePlay::create();

    scene->addChild(layer);

    return scene;
}

bool GamePlay::init()
{

    if( !Layer::init() )
    {
	return false;
    }

    Size size = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    b2Vec2 gravity;
    gravity.Set(0.0f, -9.8f);

    _world = new b2World(gravity);
    _world->SetAllowSleeping(true);
    _world->SetContinuousPhysics(true);

    _world->SetDebugDraw(&_debugDraw);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
//    flags += b2Draw::e_jointBit;
//    flags += b2Draw::e_centerOfMassBit;
//    flags += b2Draw::e_pairBit;
//    flags += b2Draw::e_shapeBit;
    _debugDraw.SetFlags(flags);

    tileMap = TMXTiledMap::create("level1.tmx");
    tileMap->setPosition(Point(origin.x, origin.y));
    if(tileMap != nullptr)
        this->addChild(tileMap, -1);

//    TiledBodyCreator::initCollisionMap(tileMap, _world);

    prepareWorldLayer(tileMap);

    mainChar = HeroMC::create("mc.png");
    mainChar->setPosition(Point(origin.x+mainChar->getContentSize().width/2, origin.y+size.height-mainChar->getContentSize().height/2));

    this->addChild(mainChar);

    mainChar->SetPhysics(_world);

    scheduleUpdate();

    return true;
}

void GamePlay::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Layer::draw(renderer, transform, flags);
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(GamePlay::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
//    _world->DrawDebugData();
}

void GamePlay::onDraw(const Mat4 &transform, uint32_t flags)
{
    Director *director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

    _world->DrawDebugData();
    CHECK_GL_ERROR_DEBUG();
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void GamePlay::update(float dt)
{
    int velocityIterations = 8;
    int positionIterations = 2;

    _world->Step(dt, velocityIterations, positionIterations);

    for(b2Body *b = _world->GetBodyList(); b; b = b->GetNext())
    {
	if(b->GetUserData())
	{
	    Sprite* physicsSprite = (Sprite*)b->GetUserData();
	    b2Vec2 position = b->GetPosition();
	    physicsSprite->setPosition(position.x, position.y);
//	    physicsSprite->update(dt);
	}
    }
}

void GamePlay::prepareWorldLayer(TMXTiledMap *map)
{
    for(auto &object : map->getChildren())
    {
	auto *layer = dynamic_cast<TMXLayer*> (object);
	if(layer != nullptr)
	    this->createWorldPhysics(layer);
    }
}

void GamePlay::createWorldPhysics(TMXLayer* layer)
{
   Size layerSize = layer->getLayerSize();
   for( int y = 0; y<layerSize.height; ++y )
   {
	for( int x=0; x<layerSize.width; ++x)
	{
	    auto tileSprite = layer->getTileAt(Point(x, y));
	    if(tileSprite)
		this->createPhysicsForTile(layer, x, y);
	}
   }
}

void GamePlay::createPhysicsForTile(TMXLayer *layer, int x, int y)
{
    auto p = layer->getPositionAt(Point(x, y));
    auto tile = layer->getTileAt(Point(x,y));
    auto tileSize = this->tileMap->getTileSize();

    const float pixelPerMeter = PTM_RATIO;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(
	p.x + tileSize.width/2,
	p.y + tileSize.height/2);
    bodyDef.userData = tile;

    b2Body *body = _world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(
	tileSize.width*0.5f,
	tileSize.height*0.5f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}
