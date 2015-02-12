#ifndef __HERO_MC__
#define __HERO_MC__

#include "cocos2d.h"
#include "GameCharacter.h"

class HeroMC : public GameCharacter
{
    enum
    {
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
    };

    enum
    {
	MINE_SIDE,
	MINE_BOTTOM
    }_mineDireciton;

    unsigned char _direction;

public:
    HeroMC(void);
    ~HeroMC(void);

    static HeroMC* create(const std::string& fileName);
    void update(float delta);

    void setDirection(unsigned char direction)	{	_direction = direction;	}

    b2Body* getBody()	{ 	return charBody; 	}
};

#endif	// __HERO_MC__
