#ifndef __GAMEMANAGERSCENE_H__
#define __GAMEMANAGERSCENE_H__

#include <cocos2d.h>
#include "GamePlayScene.h"
#include "HUDLayer.h"

class GameManager : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void update(float delta);

//    void update(float delta);

    CREATE_FUNC(GameManager);

private:
    GamePlay *gamePlayLayer;
    HUDLayer *hudLayer;
};


#endif	// __GAMEMANAGERSCENE_H__
