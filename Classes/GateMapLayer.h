//
//  GateMapLayer.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/24.
//
//

#ifndef GateMapLayer_h
#define GateMapLayer_h

#include "GlobalDefine.h"
#include "StartLayer.h"

class SelectGate;

class GateMapLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void onEnterTransitionDidFinish();
    void onExit();
    CREATE_FUNC(GateMapLayer);
    
    void gateOneCallBack();
    void gateTwoCallBack();
    void gateThreeCallBack();
    
    void clickCloseButton();
    void clickChallengeButton();
    
private:
    SelectGate *_selectGateMenu;
};

#endif /* GateMapLayer_h */
