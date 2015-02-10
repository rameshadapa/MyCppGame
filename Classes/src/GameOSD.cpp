#include "GameOSD.h"

USING_NS_CC;

int GameOSD::GAME_WIDTH;
int GameOSD::GAME_HEIGHT;
int GameOSD::PTM_RATIO		= 32;

GameOSD::GameOSD()
{
}

GameOSD::~GameOSD()
{
}

void GameOSD::Initialize()
{
    auto director = Director::getInstance();
    Size size = director->getVisibleSize();
    Point origin = director->getVisibleOrigin();
}

void GameOSD::InitOSD(int width, int height)
{
    GAME_WIDTH 	= width;
    GAME_HEIGHT	= height;
//    PTM_RATIO	= 32*widthMul/heightMul;
}
