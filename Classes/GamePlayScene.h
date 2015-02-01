#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include "ShaderNode.h"
#include "GameOSD.h"
#include "HeroMC.h"
#include "HUDLayer.h"
#include "GLES-Render.h"
#include "Box2D/Box2D.h"

class GamePlay : public cocos2d::Layer, public GameOSD
{
public:

    GamePlay();
    ~GamePlay();

    static cocos2d::Scene* createScene();

    virtual bool init();

    void prepareWorldLayer(cocos2d::TMXTiledMap *map);
    void createWorldPhysics(cocos2d::TMXLayer* layer);
    void createPhysicsForTile(cocos2d::TMXLayer *layer, int x, int y);

    void update(float dt);

    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);

    CREATE_FUNC(GamePlay);

private:
    //Box2D World
    b2World *_world;
    //Box2D debugDraw.
    GLESDebugDraw _debugDraw;
    ShaderNode *mask;
    cocos2d::Camera *_camera;

    cocos2d::CustomCommand _customCommand;

    //One onscreen TileMap & one Temparary tilemap.
    cocos2d::TMXTiledMap *tileMap;
    cocos2d::TMXTiledMap *tmpMap;

    //MainCharacter pointer.
    HeroMC *mainChar;
    HUDLayer *hud;
};

#endif	// __GAMEPLAY_SCENE_H__
