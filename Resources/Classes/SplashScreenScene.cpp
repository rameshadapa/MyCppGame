#include "SplashScreenScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* SplashScreen::createScene()
{
    auto scene = Scene::create();

    auto layer = SplashScreen::create();

    scene->addChild(layer);

    return scene;	
}

bool SplashScreen::init()
{
    if( !Layer::init() )
    {
	return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("HelloWorld.png");

    sprite->setPosition( Point( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ) );

    this->addChild(sprite);

    auto runCallback = CallFunc::create( CC_CALLBACK_0( SplashScreen::MenuScene, this ) );

    auto seq = Sequence::create(DelayTime::create(3.0), runCallback, NULL );

    this->runAction(seq);

    return true;
}

void SplashScreen::MenuScene()
{
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.2f, scene));
}
