//
//  TujiLayer.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/18.
//
//

#ifndef TujiLayer_h
#define TujiLayer_h

#include "GlobalDefine.h"
#include "StartLayer.h"

typedef enum {
    Mz,
    Lion,
    Stone,
    Unknown
} MonsterType;

class TujiLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TujiLayer);
    
    void selectedItemEvent(cocos2d::Ref *pSender, cocos2d::ui::ListView::EventType type);
    void clickCloseButton();
    
private:
    cocos2d::ui::ListView *_listView;
    
    cocos2d::Sprite *_mzPic;
    cocos2d::Sprite *_mzText;
    cocos2d::ui::Text *_mzLabel;
    cocos2d::Sprite *_lionPic;
    cocos2d::ui::Text *_lionLabel;
    cocos2d::Sprite *_stonePic;
    cocos2d::ui::Text *_stoneLabel;    
};

#endif /* TujiLayer_h */
