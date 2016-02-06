//
//  HelpLayer.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/22.
//
//

#ifndef HelpLayer_h
#define HelpLayer_h

#include "GlobalDefine.h"
#include "StartLayer.h"

class HelpLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelpLayer);
    
    void clickCloseButton();
    void scrollBack();
    
private:
    cocos2d::ui::Text *_text;
};

#endif /* HelpLayer_h */
