//
//  PauseLayer.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/12/1.
//
//

#ifndef PauseLayer_h
#define PauseLayer_h

#include "GlobalDefine.h"

class PauseLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene(cocos2d::RenderTexture *rt);
    
    virtual bool init();
    
    CREATE_FUNC(PauseLayer);

    void setMusic(cocos2d::Ref *pSender);
    void clickPlayButton();
    void clickBackButton();
    void clickAgainButton();
    void clickNextButton();
    
private:
    cocos2d::Sprite *_spriteUp;
    cocos2d::Sprite *_spriteDown;
};

#endif /* PauseLayer_h */
