#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class GamePlay : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    void prepareWorldLayer();
    void createWorldPhysics(cocos2d::TMXLayer* layer);
    void createPhysicsForTile(cocos2d::TMXLayer *layer, int x, int y, float width, float height);

    CREATE_FUNC(GamePlay);

private:
    b2World *_world;
    b2Body *_mcBodyDef;
    cocos2d::TMXTiledMap *tileMap;
};

#endif	// __GAMEPLAY_SCENE_H__
