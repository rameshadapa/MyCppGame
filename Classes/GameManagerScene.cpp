
#include "GameManagerScene.h"
#include "GamePlayScene.h"
#include "HUDLayer.h"

USING_NS_CC;

Scene* GameManager::createScene()
{
    Scene *scene = Scene::create();

    Layer *layer = GameManager::create();

    scene->addChild(layer);
    return scene;
}

bool GameManager::init()
{
    if( !Layer::init() )
    {
	return false;
    }

    gamePlayLayer = GamePlay::create();
    this->addChild(gamePlayLayer, 1);

    hudLayer = HUDLayer::create();
    this->addChild(hudLayer, 100);
    return true;
}
