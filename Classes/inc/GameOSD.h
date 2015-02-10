#ifndef __GAMEOSD_H__
#define __GAMEOSD_H__

#include "cocos2d.h"
#include "defs.h"

class GameOSD
{
public:
    static float GAME_WIDTH;
    static float GAME_HEIGHT;

    static float PTM_RATIO;		//PixelToMeter Ratio.

    GameOSD();
    ~GameOSD();
   
    static void Initialize();
    static void InitOSD(float multiplier, float devider);
};

#endif		// __GAMEOSD_H__
