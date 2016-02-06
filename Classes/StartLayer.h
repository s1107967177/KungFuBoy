//
//  StartLayer.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/15.
//
//

#ifndef StartLayer_h
#define StartLayer_h

#include "GlobalDefine.h"
#include "MijiLayer.h"
#include "TujiLayer.h"
#include "SetLayer.h"
#include "HelpLayer.h"
#include "GateMapLayer.h"

class StartLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    void onEnterTransitionDidFinish();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(StartLayer);
    
private:
    //开始主界面按钮控件监听事件
    void clickTuji();
    void clickMiji();
    void clickSet();
    void clickHelp();
    void clickCG();
    void clickTZ();
    
};

#endif /* StartLayer_h */
