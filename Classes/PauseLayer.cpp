//
//  PauseLayer.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/12/1.
//
//

#include "PauseLayer.h"
#include "StartLayer.h"
#include "GameLayer.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;

Scene *PauseLayer::createScene(RenderTexture *rt)
{
    Scene *scene = Scene::create();
    PauseLayer *layer = PauseLayer::create();
    auto sprite = Sprite::createWithTexture(rt->getSprite()->getTexture());
    sprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
    sprite->setFlippedY(true);
    scene->addChild(sprite, 0);
    scene->addChild(layer);
    return scene;
}

bool PauseLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    auto rootNode = CSLoader::createNode("PauseScene.csb");
    addChild(rootNode);
    
    _spriteUp = rootNode->getChildByName<Sprite*>("pauseBG1");
    _spriteDown = rootNode->getChildByName<Sprite*>("pauseBG2");
    
    auto playButton = _spriteUp->getChildByName<Button*>("playButton");
    playButton->addClickEventListener(CC_CALLBACK_0(PauseLayer::clickPlayButton, this));
    auto backButton = _spriteUp->getChildByName<Button*>("backButton");
    backButton->addClickEventListener(CC_CALLBACK_0(PauseLayer::clickBackButton, this));
    auto againButton = _spriteUp->getChildByName<Button*>("againButton");
    againButton->addClickEventListener(CC_CALLBACK_0(PauseLayer::clickAgainButton, this));
    auto nextButton = _spriteUp->getChildByName<Button*>("nextButton");
    nextButton->addClickEventListener(CC_CALLBACK_0(PauseLayer::clickNextButton, this));

    auto musicOn = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("musicOn.png"),
        Sprite::createWithSpriteFrameName("musicOff.png"));
    auto musicOff = MenuItemSprite::create(
        Sprite::createWithSpriteFrameName("musicOff.png"),
        Sprite::createWithSpriteFrameName("musicSelected.png"));
    auto musicToggle = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(PauseLayer::setMusic, this), musicOn, musicOff, NULL);
    musicToggle->setPosition(190, 180);
    
    auto menu = Menu::create(musicToggle, NULL);
    menu->setPosition(Vec2::ZERO);
    _spriteUp->addChild(menu);
 
    auto moveDown = MoveBy::create(0.6f, Vec2(0, - (_spriteUp->getContentSize().height)));
    auto moveUp = MoveBy::create(0.6f, Vec2(0, _spriteDown->getContentSize().height));
    
    _spriteUp->runAction(moveDown);
    _spriteDown->runAction(moveUp);
    
    return true;
}

void PauseLayer::setMusic(Ref *pSender)
{
    PLAY_EFFECT;
    auto musicTemp = (MenuItemToggle*)pSender;
    if (musicTemp->getSelectedIndex() == 1) {
        audioEngine->pauseBackgroundMusic();
        setBoolToXML(MUSIC_KEY, false);
    }
    else {
        audioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSIC_VOL));
        audioEngine->resumeBackgroundMusic();
        setBoolToXML(MUSIC_KEY, true);
    }
    UserDefault::getInstance()->flush();
}

void PauseLayer::clickPlayButton()
{
    PLAY_EFFECT;
    auto moveUp = MoveBy::create(0.6f, Vec2(0, _spriteUp->getContentSize().height));
    auto moveDown = MoveBy::create(0.6f, Vec2(0, -(_spriteDown->getContentSize().height)));
    auto replace = CallFunc::create([](){Director::getInstance()->popScene();});
    _spriteUp->runAction(Sequence::create(moveUp, replace, NULL));
    _spriteDown->runAction(moveDown);
}

void PauseLayer::clickBackButton()
{
    PLAY_EFFECT;
    audioEngine->pauseBackgroundMusic();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, StartLayer::createScene()));
}

void PauseLayer::clickAgainButton()
{
    PLAY_EFFECT;
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameLayer::createScene()));
}

void PauseLayer::clickNextButton()
{
    PLAY_EFFECT;
    int selectedGate = getIntFromXML(SELECT_GATE);
    if ( ++selectedGate <= 3)
    {
        setIntToXML(SELECT_GATE, selectedGate);
        Director::getInstance()->replaceScene(GameLayer::createScene());
    }
}