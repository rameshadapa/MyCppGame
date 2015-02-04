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
    }_direction;

    enum
    {
	MINE_SIDE,
	MINE_BOTTOM
    }_mineDireciton;

public:
    HeroMC(void);
    ~HeroMC(void);

    void update(float delta);
};

#endif	// __HERO_MC__
