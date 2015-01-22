#include "GamePlayScene.h"
#include "ShaderLayer.h"
#include "ShaderNode.h"

USING_NS_CC;

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
    gravity.Set(0.0f, 0.98f);

    _world = new b2World(gravity);
    _world->SetAllowSleeping(true);
    _world->SetContinuousPhysics(true);

    tileMap = TMXTiledMap::create("level1.tmx");
    tileMap->setPosition(Point(origin.x, origin.y));
    if(tileMap != nullptr)
        this->addChild(tileMap);
/*
    auto label = LabelTTF::create("Game Play", "Arial", 40);

    label->setPosition(Point(origin.x + size.width/2, origin.y + size.height/2 ));

    this->addChild(label);
*/
//    auto shaderLayer = ShaderLayer::create("game.glsl");

//    this->addChild(shaderLayer);

//    initGLProgramState("LensFlare.fsh");

//    auto sn = ShaderNode::shaderNodeWithVertex("", "Flower.fsh");
//    auto sn = ShaderNode::shaderNodeWithVertex("", "ssbg.fsh");

//    auto s = Director::getInstance()->getWinSize();
//    sn->setPosition(Vec2(size.width/2, size.height/2));
//    sn->setContentSize(Size(size.width/8,size.height/8));
//    addChild(sn);

//    ParticleSystem *emitter = new ParticleSystemQuad();
/*    auto batchNode = ParticleBatchNode::create("fire.png", 3000);
    auto emitter = ParticleSystemQuad::createWithTotalParticles(100);
    emitter->retain();
    emitter->setPosition(Point(origin.x + size.width/2, origin.y + size.height/2 ));
//    emitter->initWithTotalParticles(38);
    emitter->setAngle(90);
    emitter->setAngleVar(0);
    emitter->setLife(0.9);
    emitter->setLifeVar(0.2);
    emitter->setStartSize(30);
    emitter->setStartSizeVar(8);
    emitter->setEndSize(25);
    emitter->setEndSizeVar(10);

    emitter->setDuration(ParticleSystem::DURATION_INFINITY);

        // radius mode
    emitter->setEmitterMode(ParticleSystem::Mode::GRAVITY);

    emitter->setSpeed(45);
    emitter->setSpeedVar(2);

    emitter->setStartColor(Color4F(0.26*255, 0.25*255, 0.72*255, 255));
    emitter->setEndColor(Color4F(0, 0, 0, 255));
    emitter->setTexture(batchNode->getTexture());

    emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
    emitter->setPositionType(ParticleSystem::PositionType::FREE);
    emitter->release();
 
    this->addChild(emitter);
*/
/*
    auto _directionalLight = DirectionLight::create(Vec3(-1.0f, -1.0f, 0.0f), Color3B(200, 200, 200));
    _directionalLight->retain();
    _directionalLight->setEnabled(false);
    addChild(_directionalLight);

    auto tintto1 = TintTo::create(4, 255, 0, 0);
    auto tintto2 = TintTo::create(4, 0, 255, 0);
    auto tintto3 = TintTo::create(4, 0, 0, 255);
    auto tintto4 = TintTo::create(4, 255, 255, 255);
    auto seq = Sequence::create(tintto1,tintto2, tintto3, tintto4, nullptr);
    _directionalLight->runAction(RepeatForever::create(seq));
*/

/*    auto camera = Camera::createPerspective(60, (GLfloat)size.width/size.height, 1, 1000);
    camera->setCameraFlag(CameraFlag::USER1);
    addChild(camera);

    label->setCameraMask((unsigned short)CameraFlag::USER1);*/
/*
    auto directionLight = DirectionLight::create(Vec3(0.0f, 0.0f, 0.0f), Color3B(200, 200, 200));
    this->addChild(directionLight);
    directionLight->setEnabled(true);*/
//    directionLight->setLightFlag(LightFlag::LIGHT0);

    return true;
}

void GamePlay::prepareWorldLayer()
{
    for(auto &object : this->tileMap->getChildren())
    {
	auto *layer = dynamic_cast<TMXLayer*> (object);
	if(layer != nullptr)
	    this->createWorldPhysics(layer);
    }
}


void GamePlay::createWorldPhysics(TMXLayer* layer)
{
   Size layerSize = layer->getLayerSize();
   for( int x = 0; x<layerSize.width; ++x )
   {
	for( int y=0; y<layerSize.height; ++y)
	{
	    auto tileSprite = layer->getTileAt(Point(x, y));
	    if(tileSprite)
		this->createPhysicsForTile(layer, x, y, 1.1f, 1.1f);
	}
   }
}

void GamePlay::createPhysicsForTile(TMXLayer *layer, int x, int y, float width, float height)
{
    auto p = layer->getPositionAt(Point(x, y));
    auto tileSize = this->tileMap->getTileSize();

    const float pixelPerMeter = 32.0f;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(
	(p.x + (tileSize.width / 2.0f) ) / pixelPerMeter,
	(p.y + (tileSize.height/ 2.0f) ) / pixelPerMeter);

    b2Body *body = _world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(
	(tileSize.width/pixelPerMeter) * 0.5f * width,
	(tileSize.height/pixelPerMeter) * 0.5f *height);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.0f;

    b2Fixture *fixture;
    fixture = body->CreateFixture(&fixtureDef);
}
