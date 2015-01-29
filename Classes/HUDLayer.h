#ifndef __HUDLAYER_H__
#define __HUDLAYER_H__

#include "cocos2d.h"

class HUDLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    void onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
    void onTouchesCancelled(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);

    CREATE_FUNC(HUDLayer);
private:
//    static cocos2d::Map<int, cocos2d::Vec2*> s_map;

};

#endif	// __HUDLAYER_H__
