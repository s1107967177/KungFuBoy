//
//  GateMapLayer.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/24.
//
//

#include "GateMapLayer.h"
#include "SelectGate.h"
#include "GameLayer.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;

Scene *GateMapLayer::createScene()
{
    Scene *scene = Scene::create();
    GateMapLayer *layer = GateMapLayer::create();
    scene->addChild(layer);
    return scene;
}

void GateMapLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    if (getBoolFromXML(MUSIC_KEY)) {
        audioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSIC_VOL));
        audioEngine->playBackgroundMusic("Sound/gateMap.wav", true);
    } else {
        audioEngine->pauseBackgroundMusic();
    }
}

void GateMapLayer::onExit()
{
    Layer::onExit();
    audioEngine->pauseBackgroundMusic();
}

bool GateMapLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("GateMapScene.csb");
    addChild(rootNode);
    
    Button *closeButton = rootNode->getChildByName<Button*>("closeButton");
    closeButton->addClickEventListener(
        CC_CALLBACK_0(GateMapLayer::clickCloseButton, this));
    
    Button *challengeButton = rootNode->getChildByName<Button*>("challengeButton");
    challengeButton->addClickEventListener(
        CC_CALLBACK_0(GateMapLayer::clickChallengeButton, this));
    
    auto gateOneItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("Gate_1.png"),
        Sprite::createWithSpriteFrameName("Gate_1.png"),
        CC_CALLBACK_0(GateMapLayer::gateOneCallBack, this));
    
    auto gateTwoItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("Gate_2.png"),
        Sprite::createWithSpriteFrameName("Gate_2.png"),
        CC_CALLBACK_0(GateMapLayer::gateTwoCallBack, this));
    
    auto gateThreeItem = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("Gate_3.png"),
        Sprite::createWithSpriteFrameName("Gate_3.png"),
        CC_CALLBACK_0(GateMapLayer::gateThreeCallBack, this));
    
    _selectGateMenu = SelectGate::create();
    _selectGateMenu->addMenuItem(gateOneItem);
    _selectGateMenu->addMenuItem(gateTwoItem);
    _selectGateMenu->addMenuItem(gateThreeItem);
    _selectGateMenu->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 + 74);
    addChild(_selectGateMenu, 1);
    
    return true;
}

void GateMapLayer::clickCloseButton()
{
    log("Close GateMap.");
    PLAY_EFFECT;
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, StartLayer::createScene()));
}

void GateMapLayer::clickChallengeButton()
{
    PLAY_EFFECT;
    _selectGateMenu->getCurrentItem()->activate();
}

void GateMapLayer::gateOneCallBack()
{
    PLAY_EFFECT;
    setIntToXML(GAME_LEVEL_KEY, 1);
    setIntToXML(SELECT_GATE, 1);
    UserDefault::getInstance()->flush();
    log("First gate selected!");
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameLayer::createScene()));
}

void GateMapLayer::gateTwoCallBack()
{
    PLAY_EFFECT;
    setIntToXML(GAME_LEVEL_KEY, 2);
    setIntToXML(SELECT_GATE, 2);
    UserDefault::getInstance()->flush();
    log("Second gate selected!");
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameLayer::createScene()));
}

void GateMapLayer::gateThreeCallBack()
{
    PLAY_EFFECT;
    setIntToXML(GAME_LEVEL_KEY, 3);
    setIntToXML(SELECT_GATE, 3);
    UserDefault::getInstance()->flush();
    log("Third gate selected!");
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameLayer::createScene()));
}