//
//  SplashLayer.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/15.
//
//

#include "SplashLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene *SplashLayer::createScene()
{
    Scene *scene = Scene::create();
    SplashLayer *layer = SplashLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SplashLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("LogoScene.csb");
    addChild(rootNode);
    
    //首次运行初始化用户数据
    if (!getBoolFromXML("_IS_EXISTED")) {
        initUserData();
        setBoolToXML("_IS_EXISTED", true);
        UserDefault::getInstance()->flush();
    }
    
    _numOfLoad = 0;
    
    //图片和声音的异步加载
    //主界面
    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/startGame.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
    //图籍
    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/gameLayer.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
    //设置
    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/setLayer.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
    //秘籍
    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/cheatsLayer.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
    //选关
    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/gateMap.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
    //暂停
    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/pauseLayer.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
    
    //英雄
    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/hero.png",  CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/heroComobo.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/heroGun.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
    
    //怪物
    Director::getInstance()->getTextureCache()->addImageAsync("pnglist/monster.png",CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
    
    _loadingAudioThread = new std::thread(&SplashLayer::loadingAudio, this);
    
    return true;
}

void SplashLayer::loadingTextureCallBack(Texture2D *texture)
{
    switch (_numOfLoad++) {
        case 0:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                                                     "pnglist/startGame.plist", texture);
            break;
        case 1:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                                                     "pnglist/gameLayer.plist", texture);
            break;
        case 2:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                                                     "pnglist/setLayer.plist", texture);
            break;
        case 3:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                                                     "pnglist/cheatsLayer.plist", texture);
            break;
        case 4:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                                                     "pnglist/gateMap.plist", texture);
            break;
        case 5:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                                                     "pnglist/pauseLayer.plist", texture);
            break;
        case 6:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                                                     "pnglist/hero.plist", texture);
            break;
        case 7:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                                                     "pnglist/heroComobo.plist", texture);
            break;
        case 8:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                                                     "pnglist/heroGun.plist", texture);
            break;
        case 9:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                                                    "pnglist/monster.plist", texture);
            schedule(schedule_selector(SplashLayer::nextScene), 1.0f, 0, 1.0f);
            break;
        default:
            break;
    }
}

void SplashLayer::loadingAudio()
{
    log("LoadingAudio...");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/startBGM.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("Sound/button.wav");
}

void SplashLayer::initUserData()
{
    setIntToXML(GAME_LEVEL_KEY, 1);
    setIntToXML(HERO_ENERGY_KEY, 10);
    setIntToXML(HERO_COIN_KEY, 1000);
    setBoolToXML(SOUND_KEY, true);
    setBoolToXML(MUSIC_KEY, true);
    setFloatToXML(SOUND_VOL, 0.80f);
    setFloatToXML(MUSIC_VOL, 0.35f);
    //刷新
    UserDefault::getInstance()->flush();
}

void SplashLayer::nextScene(float delta)
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, StartLayer::createScene()));
    
}

void SplashLayer::onExit()
{
    Layer::onExit();
    _loadingAudioThread->join();
    CC_SAFE_DELETE(_loadingAudioThread);
    unschedule(schedule_selector(SplashLayer::nextScene));
}
