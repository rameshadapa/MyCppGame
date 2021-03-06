#ifndef __HUDLAYER_H__
#define __HUDLAYER_H__

#include "cocos2d.h"
#include "defs.h"
#include "HeroMC.h"
#include "ShaderNode.h"

class HUDLayer : public cocos2d::Layer, public GameOSD
{
public:
//    static cocos2d::Scene* createScene();
    virtual bool init();

    void setGameCharacter(HeroMC *mc) 	{	gameChar = mc;	}

    void onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
    void onTouchesCancelled(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);

    void leftPress(cocos2d::Ref *sender);
    void rightPress(cocos2d::Ref *sender);

    void update(float delta);

    CREATE_FUNC(HUDLayer);
private:

    HeroMC *gameChar;
    ShaderNode *mask;

    cocos2d::Sprite *leftButton;
    cocos2d::Sprite *rightButton;

    cocos2d::Sprite *mineTool;
    cocos2d::Sprite *jumpButton;
    cocos2d::MenuItemImage *attackButton;
//    static cocos2d::Map<int, cocos2d::Vec2*> s_map;

public:
    static bool moveLeft;//	= false;
    static bool moveRight;//	= false;

    static bool pressMine;
    static bool pressJump;//	= false;
    static constexpr bool pressAttack	= false;

};

#endif	// __HUDLAYER_H__
