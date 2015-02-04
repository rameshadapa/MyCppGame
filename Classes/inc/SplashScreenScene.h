#ifndef __SPLASHSCREEN_SCENE__
#define __SPLASHSCREEN_SCENE__

#include "cocos2d.h"

class SplashScreen : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void MenuScene();

    CREATE_FUNC(SplashScreen); 	
};

#endif		// __SPLASHSCREEN_SCENE__
