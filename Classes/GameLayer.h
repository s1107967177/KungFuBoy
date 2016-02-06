//
//  GameLayer.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/29.
//
//

#ifndef GameLayer_h
#define GameLayer_h

#include "GlobalDefine.h"
#include "extensions/cocos-ext.h"

class Hero;
class Monster;
class GameMap;

class GameLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    void onEnterTransitionDidFinish();
    
    virtual void update(float delta);
    
    static cocos2d::Scene *createScene();
    CREATE_FUNC(GameLayer);
    
    //暂停
    void gamePause();
    
    //技能
    void fistAttack();
    void footAttack();
    void comboAttack();
    void jump();
    void backward(cocos2d::Ref *pSender, cocos2d::extension::Control::EventType type);
    void forward(cocos2d::Ref *pSender, cocos2d::extension::Control::EventType type);
    
    
private:
    bool isAttackingMonster(Hero *hero, Monster *monster);
    void moveXWhileJumping();
    void gameOver();
    void gameVictory();
    
    Hero *_hero;
    Monster *_monster;
    GameMap *_myMap;
    cocos2d::Sprite* _comboSprite;
    
    int _selectedGate;
    float _velocity;
    bool _runDirection;
    bool _isJumping;
    bool _isRunning;
    
    cocos2d::ui::Button *_backwardButton;
    cocos2d::ui::Button *_forwardButton;
    
    cocos2d::ui::LoadingBar *_hpBar;
    cocos2d::ui::LoadingBar *_mpBar;
    
    cocos2d::RenderTexture *_render;
    cocos2d::RenderTexture *_renderResult;
};

#endif /* GameLayer_h */
