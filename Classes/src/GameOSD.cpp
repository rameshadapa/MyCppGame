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

void GameOSD::InitOSD(int widthMul, int heightMul)
{
    GAME_WIDTH 	= 960*widthMul;
    GAME_HEIGHT	= 640*heightMul;
    PTM_RATIO	= 32*widthMul/heightMul;
}