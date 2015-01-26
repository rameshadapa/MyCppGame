#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include "GLES-Render.h"
#include "Box2D/Box2D.h"

class GamePlay : public cocos2d::Layer
{
public:

    GamePlay();
    ~GamePlay();

    static cocos2d::Scene* createScene();

    virtual bool init();

    void prepareWorldLayer();
    void createWorldPhysics(cocos2d::TMXLayer* layer);
    void createPhysicsForTile(cocos2d::TMXLayer *layer, int x, int y, float width, float height);

    void update(float dt);

    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, bool transformUpdated);

    CREATE_FUNC(GamePlay);

private:
    GLESDebugDraw *_debugDraw;
    b2World *_world;
    b2Body *_mcBodyDef;
    cocos2d::TMXTiledMap *tileMap;
};

#endif	// __GAMEPLAY_SCENE_H__
