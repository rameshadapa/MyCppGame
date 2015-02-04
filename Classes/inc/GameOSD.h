#ifndef __GAMEOSD_H__
#define __GAMEOSD_H__

#include "cocos2d.h"
#include "defs.h"

class GameOSD
{
public:
    static int GAME_WIDTH;
    static int GAME_HEIGHT;

    static int PTM_RATIO;		//PixelToMeter Ratio.

    GameOSD();
    ~GameOSD();
   
    static void Initialize();
    static void InitOSD(int multiplier, int devider);
};

#endif		// __GAMEOSD_H__
