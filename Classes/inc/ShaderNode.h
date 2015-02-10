#ifndef __SHADERNODE_H__
#define __SHADERNODE_H__

#include "cocos2d.h"
#include "GameOSD.h"

class ShaderNode : public cocos2d::Node, public GameOSD
{
public:
    static ShaderNode* shaderNodeWithVertex(const std::string &vert, const std::string &frag);

    virtual void update(float dt);
    virtual void setPosition(const cocos2d::Vec2 &newPosition);
    virtual void setLightPos(const cocos2d::Vec2 &position);
    virtual void setLightCount(float lightCount)	{	_lightCount = lightCount;	}
    virtual void isLightMask(bool type) {	_type = type;	}

    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

protected:
    ShaderNode();
    ~ShaderNode();

    bool initWithVertex(const std::string &vert, const std::string &frag);
    void loadShaderVertex(const std::string &vert, const std::string &frag);

    void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);

    cocos2d::Vec2 _center;
    cocos2d::Vec2 _resolution;
    cocos2d::Vec2 _lightPos;
    float	_lightCount;
    float      _time;

    std::string _vertFileName;
    std::string _fragFileName;
    cocos2d::CustomCommand _customCommand;

    bool _type;
};

#endif
