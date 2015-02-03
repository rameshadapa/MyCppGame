#ifndef __GAMEMANAGERSCENE_H__
#define __GAMEMANAGERSCENE_H__

#include <cocos2d.h>

class GameManager : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

//    void update(float delta);

    CREATE_FUNC(GameManager);

private:
    cocos2d::Layer *gamePlayLayer;
    cocos2d::Layer *hudLayer;
};


#endif	// __GAMEMANAGERSCENE_H__
