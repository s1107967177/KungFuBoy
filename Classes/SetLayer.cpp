//
//  SetLayer.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/19.
//
//

#include "SetLayer.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;

Scene *SetLayer::createScene()
{
    Scene *scene = Scene::create();
    SetLayer *layer = SetLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SetLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("SetScene.csb");
    
    Button *closeButton = rootNode->getChildByName<Button*>("closeButton");
    closeButton->addClickEventListener(CC_CALLBACK_0(SetLayer::clickCloseButton, this));
    
    _musicVolume = getFloatFromXML(MUSIC_VOL) ;
    _soundVolume = getFloatFromXML(SOUND_VOL);
    
    _musicSlider = rootNode->getChildByName<Slider*>("musicSlider");
    _musicSlider->setPercent(static_cast<int>(_musicVolume * 100));
    _musicSlider->addEventListener(CC_CALLBACK_2(SetLayer::changeMusicVol, this));
    
    _soundSlider = rootNode->getChildByName<Slider*>("soundSlider");
    _soundSlider->setPercent(static_cast<int>(_soundVolume * 100));
    _soundSlider->addEventListener(CC_CALLBACK_2(SetLayer::changeSoundVol, this));
    
    _musicToggle = rootNode->getChildByName<CheckBox*>("musicToggle");
    _musicToggle->setSelected(getBoolFromXML(MUSIC_KEY));
    _musicToggle->addEventListener(CC_CALLBACK_2(SetLayer::turnMusicToggle, this));
    
    _soundToggle = rootNode->getChildByName<CheckBox*>("soundToggle");
    _soundToggle->setSelected(getBoolFromXML(SOUND_KEY));
    _soundToggle->addEventListener(CC_CALLBACK_2(SetLayer::turnSoundToggle, this));
    
    Button *saveButton = rootNode->getChildByName<Button*>("saveSettings");
    saveButton->addClickEventListener(CC_CALLBACK_0(SetLayer::clickSaveButton, this));
    
    Button *restoreButton = rootNode->getChildByName<Button*>("restoreSettings");
    restoreButton->addClickEventListener(CC_CALLBACK_0(SetLayer::clickRestoreButton, this));
    
    addChild(rootNode);
    
    return true;
}

void SetLayer::clickCloseButton()
{
    log("Close Setting.");
    PLAY_EFFECT;
    Director::getInstance()->replaceScene(StartLayer::createScene());
}

void SetLayer::changeMusicVol(Ref *pSender, Slider::EventType type)
{
    _musicVolume = static_cast<Slider*>(pSender)->getPercent() / 100.0f;
    audioEngine->setBackgroundMusicVolume(_musicVolume);
    if (_musicToggle->isSelected() == false) {
        _musicToggle->setSelected(true);
        audioEngine->resumeBackgroundMusic();
    }
    log("Current music volume is %.2f", _musicVolume);
}

void SetLayer::changeSoundVol(Ref *pSender, Slider::EventType type)
{
    _soundVolume = static_cast<Slider*>(pSender)->getPercent() / 100.0f;
    audioEngine->setEffectsVolume(_soundVolume);
    if (_soundToggle->isSelected() == false) {
        _soundToggle->setSelected(true);
        audioEngine->resumeAllEffects();
    }
    log("Current sound volume is %.2f", _soundVolume);
}

void SetLayer::clickSaveButton()
{
    log("Save settings.");
    
    if (_musicToggle->isSelected()) {
        setBoolToXML(MUSIC_KEY, true);
        setFloatToXML(MUSIC_VOL, _musicVolume);
    } else {
        setBoolToXML(MUSIC_KEY, false);
        setFloatToXML(MUSIC_VOL, 0.0f);
    }
    
    if (_soundToggle->isSelected()) {
        setBoolToXML(SOUND_KEY, true);
        setFloatToXML(SOUND_VOL, _soundVolume);
    } else {
        setBoolToXML(SOUND_KEY, false);
        setFloatToXML(SOUND_VOL, 0.0f);
    }
    UserDefault::getInstance()->flush();
    
    PLAY_EFFECT;
}

void SetLayer::clickRestoreButton()
{
    log("Restore settings.");
    audioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSIC_VOL));
    audioEngine->setEffectsVolume(getFloatFromXML(SOUND_VOL));
    _musicToggle->setSelected(getBoolFromXML(MUSIC_KEY));
    _musicSlider->setPercent(static_cast<int>(getFloatFromXML(MUSIC_VOL) * 100));
    _soundToggle->setSelected(getBoolFromXML(SOUND_KEY));
    _soundSlider->setPercent(static_cast<int>(getFloatFromXML(SOUND_VOL) * 100));
    PLAY_EFFECT;
}

void SetLayer::turnMusicToggle(Ref *pSender, CheckBox::EventType type)
{
    if (type == CheckBox::EventType::UNSELECTED) {
        audioEngine->pauseBackgroundMusic();
        _musicSlider->setPercent(0);
    } else {
        audioEngine->resumeBackgroundMusic();
        _musicSlider->setPercent(_musicVolume * 100);
    }
    PLAY_EFFECT;
}

void SetLayer::turnSoundToggle(Ref *pSender, CheckBox::EventType type)
{
    if (type == CheckBox::EventType::UNSELECTED) {
        audioEngine->stopAllEffects();
        _soundSlider->setPercent(0);
    } else {
        audioEngine->resumeAllEffects();
        _soundSlider->setPercent(_soundVolume * 100);
    }
    audioEngine->playEffect("Sound/button.wav");
}