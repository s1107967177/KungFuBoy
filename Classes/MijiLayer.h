//
//  MijiLayer.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/17.
//
//

#ifndef MijiLayer_h
#define MijiLayer_h

#include "GlobalDefine.h"
#include "StartLayer.h"

class MijiLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MijiLayer);

private:
    cocos2d::Sprite *spriteBG;
    cocos2d::Sprite *interface_1;
    cocos2d::Sprite *interface_2;
    
    bool leftFlag, rightFlag;

    void clickCloseButton();
    void clickNextLeftButton();
    void clickNextRightButton();
};

#endif /* MijiLayer_h */
