#include "GameOSD.h"

USING_NS_CC;

float GameOSD::GAME_WIDTH;
float GameOSD::GAME_HEIGHT;
float GameOSD::PTM_RATIO		= 32;

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

void GameOSD::InitOSD(float width, float height)
{
    GAME_WIDTH 	= width;
    GAME_HEIGHT	= height;
//    PTM_RATIO	= 32*widthMul/heightMul;
}
