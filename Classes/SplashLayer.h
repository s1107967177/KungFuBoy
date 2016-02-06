//
//  SplashLayer.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/15.
//
//

#ifndef SplashLayer_h
#define SplashLayer_h

#include "StartLayer.h"
#include "GlobalDefine.h"

class SplashLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(SplashLayer);
 
private:
    cocos2d::Sprite *_logoSprite;
    //场景切换
    void nextScene(float delta);
    void loadingTextureCallBack(cocos2d::Texture2D *texture);
    void loadingAudio();
    void onExit();
    //初始化用户数据
    void initUserData();
    int _numOfLoad;
    std::thread * _loadingAudioThread;
   
};

#endif /* SplashLayer_h */
