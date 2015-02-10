#include "GamePlayScene.h"
#include "GameOSD.h"
#include "HeroMC.h"
#include "GameObject.h"
#include "HUDLayer.h"

USING_NS_CC;

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
    delete _world;
}
/*
Scene* GamePlay::createScene()
{
    auto scene = Scene::create();
  
    auto layer = GamePlay::create();

    scene->addChild(layer);

    return scene;
}
*/
bool GamePlay::init()
{

    if( !Layer::init() )
    {
	return false;
    }

    Size size = Size(GAME_WIDTH, GAME_HEIGHT);
    Point origin = Director::getInstance()->getVisibleOrigin();

    b2Vec2 gravity;
    gravity.Set(0.0f, GRAVITY_IN_PIXELS);

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

    tileMap = TMXTiledMap::create("level2.tmx");
    CCLOG("Origin::: [%f %f]", origin.x, origin.y);

    this->addChild(tileMap, -1);

    tileMap->setAnchorPoint(Point::ZERO);     
    Size CC_UNUSED s = tileMap->getContentSize();
    CCLOG("Map Size:: [%f  %f]", s.width,s.height);
    tileMap->setPosition(Point(origin.x, origin.y - s.height + size.height));

    prepareWorldLayer(tileMap);

    mainChar = (HeroMC*)HeroMC::create("mc.png");
    mainChar->setPosition(Point(origin.x+size.width/2.0f, origin.y+size.height/2.0f));

    this->addChild(mainChar, 5);

    mainChar->setPhysics(_world);

//    setViewPoint(mainChar->getPosition());

//    _camera = Camera::createOrthographic(size.width, size.height, 0, 1000);
/*    _camera = Camera::createPerspective(60.0f, (GLfloat)size.width/size.height, 1, 1000);
    _camera->setCameraFlag(CameraFlag::USER1);
    auto eye = Vec3(0.0f, 100.0f, 100.0f);
    _camera->setPosition3D(eye);	//Vec3(mainChar->getPosition().x, mainChar->getPosition().y, 100));
    _camera->lookAt(Vec3(0, 0, 0), Vec3(0.0f, 1.0f, 0.0f));	//Vec3(mainChar->getPosition().x, mainChar->getPosition().y, 0), Vec3(0, 1, 0));
    _camera->retain();
    this->addChild(_camera, 10);
*/
//    scheduleUpdate();

    return true;
}

void GamePlay::setViewPoint(Point position)
{
    Size size = Size(GAME_WIDTH, GAME_HEIGHT);

    int x = MAX(position.x, size.width/2.0f);
    int y = MAX(position.y, size.height/2.0f);

    x = MIN(x, tileMap->getMapSize().width * tileMap->getTileSize().width - size.width/2.0f);
    y = MIN(y, tileMap->getMapSize().width * tileMap->getTileSize().width - size.height/2.0f); 

    Point camPoint = Point(x, y);

    Point centerOfScreen = Point(size.width/2.0f, size.height/2.0f);
    Point diff = Point(centerOfScreen, camPoint);
    this->setPosition(diff);
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
/*    Director *director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

    _world->DrawDebugData();
    CHECK_GL_ERROR_DEBUG();
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);*/
}

void GamePlay::update(float dt)
{
    int velocityIterations = 8;
    int positionIterations = 2;

    Size size = Size(GAME_WIDTH, GAME_HEIGHT);

    _world->Step(dt, velocityIterations, positionIterations);

    for(b2Body *b = _world->GetBodyList(); b; b = b->GetNext())
    {
	if(b->GetUserData())
	{
	    if(b->GetType() == b2_dynamicBody)
	    {
	    	GameCharacter* physicsSprite = (GameCharacter*)b->GetUserData();
		if(physicsSprite)
		{
		if(physicsSprite->getType() == 0)
		{
		    Vec2 pos = physicsSprite->getPosition();
		    physicsSprite->update(dt);
		    Vec2 diff = physicsSprite->getPosition() - pos;
		    this->setPosition(getPosition() - diff);
//		    setViewPoint(physicsSprite->getPosition());
		}
/*		else
		{
		    physicsSprite->setPosition(b->GetPosition().x, b->GetPosition().y);
		}*/
	    	}
	    }
	}
    }

//    float cameraX, cameraY, cameraZ;
//    float eyeX, eyeY, eyeZ;
    
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
	    {
		this->createPhysicsForTile(layer, x, y);
/*		GameObject* gameObject = new GameObject(tileSprite);
		gameObject->setBodyType(b2_staticBody);
		gameObject->setObjType(1);
		gameObject->setPhysics(_world);*/
	    }
	}
   }
}

void GamePlay::createPhysicsForTile(TMXLayer *layer, int x, int y)
{
    auto p = layer->getPositionAt(Point(x, y));
    auto tile = layer->getTileAt(Point(x,y));
    auto tileSize = this->tileMap->getTileSize();
    auto size = Size(GAME_WIDTH, GAME_HEIGHT);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(
	p.x + tileSize.width/2.0f,
	p.y - tileMap->getContentSize().height + size.height + tileSize.height/2.0f);
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
