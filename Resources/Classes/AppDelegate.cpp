#include "AppDelegate.h"
//#include "MainMenuScene.h"
#include "SplashScreenScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
//	glview->setFrameSize(320, 240);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    auto screenSize = glview->getFrameSize();

    std::vector<std::string> resDirOrders;

    CCLog("ScreenWidth:: %d, ScreenHeight:: %d", screenSize.width, screenSize.height);

    if( 2048 == screenSize.width || 2048 == screenSize.height )
    {
	resDirOrders.push_back( "ipadhd" );
	resDirOrders.push_back( "ipad" );
	resDirOrders.push_back( "iphonehd5" );
	resDirOrders.push_back( "iphonehd" );
	resDirOrders.push_back( "iphone" );

	glview->setDesignResolutionSize( 2048, 1536, ResolutionPolicy::NO_BORDER );
    }
    else if( 1024 == screenSize.width || 1024 == screenSize.height )
    {
	resDirOrders.push_back( "ipad" );
	resDirOrders.push_back( "iphonehd5" );
	resDirOrders.push_back( "iphonehd" );
	resDirOrders.push_back( "iphone" );

	glview->setDesignResolutionSize( 1024, 768, ResolutionPolicy::NO_BORDER );
    }
    else if( 1136 == screenSize.width || 1136 == screenSize.height )
    {
	resDirOrders.push_back( "iphonehd5" );
	resDirOrders.push_back( "iphonehd" );
	resDirOrders.push_back( "iphone" );

	glview->setDesignResolutionSize( 1136, 640, ResolutionPolicy::NO_BORDER );
    }
    else if( 960 == screenSize.width || 960 == screenSize.height )
    {
	CCLog("Android screenSize [%d %d]", screenSize.width, screenSize.height);
	resDirOrders.push_back( "iphonehd" );
	resDirOrders.push_back( "iphone" );
	
	glview->setDesignResolutionSize( 960, 640, ResolutionPolicy::NO_BORDER );
    }
    else
    {
	CCLog("Android screenSize [%d %d]", screenSize.width, screenSize.height);
	if( screenSize.width > 1080 )
	{
	    resDirOrders.push_back( "iphonehd" );
	    resDirOrders.push_back( "iphone" );

	    glview->setDesignResolutionSize( 960, 640, ResolutionPolicy::NO_BORDER );
	}
	else
	{
	    resDirOrders.push_back( "iphone" );

	    glview->setDesignResolutionSize( 480, 320, ResolutionPolicy::NO_BORDER );
	}
    }

    FileUtils::getInstance()->setSearchPaths( resDirOrders );

    // create a scene. it's an autorelease object
//    auto scene = HelloWorld::createScene();
    auto scene = SplashScreen::createScene();
 
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
