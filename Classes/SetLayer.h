//
//  SetLayer.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/19.
//
//

#ifndef SetLayer_h
#define SetLayer_h

#include "GlobalDefine.h"
#include "StartLayer.h"

class SetLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SetLayer);
    
    void clickCloseButton();
    void changeMusicVol(cocos2d::Ref *pSender, cocos2d::ui::Slider::EventType type);
    void changeSoundVol(cocos2d::Ref *pSender, cocos2d::ui::Slider::EventType type);
    
    void turnMusicToggle(cocos2d::Ref *pSender, cocos2d::ui::CheckBox::EventType type);
    void turnSoundToggle(cocos2d::Ref *pSender, cocos2d::ui::CheckBox::EventType type);
    
    void clickSaveButton();
    void clickRestoreButton();
    
public:
    float _musicVolume;
    float _soundVolume;
    
    cocos2d::ui::CheckBox *_musicToggle;
    cocos2d::ui::CheckBox *_soundToggle;
    
    cocos2d::ui::Slider *_musicSlider;
    cocos2d::ui::Slider *_soundSlider;
};

#endif /* SetLayer_h */
