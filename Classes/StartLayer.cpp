//
//  StartLayer.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/16.
//
//

#include "StartLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene *StartLayer::createScene()
{
    Scene *scene = Scene::create();
    StartLayer *layer = StartLayer::create();
    scene->addChild(layer);
    return scene;
}

void StartLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    //根据音乐开关来播放背景音乐
    if (getBoolFromXML(MUSIC_KEY)) {
        audioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSIC_VOL));
        if (audioEngine->isBackgroundMusicPlaying() == false) {
            audioEngine->playBackgroundMusic("Sound/startBGM.mp3", true);
        }
    } else {
        audioEngine->pauseBackgroundMusic();
    }

}

bool StartLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    //加载图片资源缓存
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/galleryLayer.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/monster.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/resultLayer.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/mapBG.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/mapMid.plist");
    
    auto rootNode = CSLoader::createNode("StartScene.csb");
    
    auto tujiButton = rootNode->getChildByName<ui::Button*>("tujiButton");
    tujiButton->addClickEventListener(CC_CALLBACK_0(StartLayer::clickTuji, this));
    
    auto mijiButton = rootNode->getChildByName<ui::Button*>("mijiButton");
    mijiButton->addClickEventListener(CC_CALLBACK_0(StartLayer::clickMiji, this));
    
    auto setButton = rootNode->getChildByName<ui::Button*>("setButton");
    setButton->addClickEventListener(CC_CALLBACK_0(StartLayer::clickSet, this));
    
    auto helpButton = rootNode->getChildByName<ui::Button*>("helpButton");
    helpButton->addClickEventListener(CC_CALLBACK_0(StartLayer::clickHelp, this));
    
    auto cgButton = rootNode->getChildByName<ui::Button*>("cgButton");
    cgButton->addClickEventListener(CC_CALLBACK_0(StartLayer::clickCG, this));
    
    auto tzButton = rootNode->getChildByName<ui::Button*>("tzButton");
    tzButton->addClickEventListener(CC_CALLBACK_0(StartLayer::clickTZ, this));
    
    addChild(rootNode);
    
    return true;
}

void StartLayer::clickTuji()
{
    log("Open Tuji.");
    PLAY_EFFECT;
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, TujiLayer::createScene()));
}

void StartLayer::clickMiji()
{
    log("Open Miji.");
    PLAY_EFFECT;
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MijiLayer::createScene()));
}

void StartLayer::clickSet()
{
    log("Open Setting.");
    PLAY_EFFECT;
    Director::getInstance()->replaceScene(SetLayer::createScene());
}

void StartLayer::clickHelp()
{
    log("Open Help.");
    PLAY_EFFECT;
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, HelpLayer::createScene()));
}

void StartLayer::clickCG()
{
    log("Open CG.");
    PLAY_EFFECT;
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GateMapLayer::createScene()));
}

void StartLayer::clickTZ()
{
    log("Open TZ.");
    PLAY_EFFECT;
}