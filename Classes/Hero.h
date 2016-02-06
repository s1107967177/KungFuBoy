//
//  Hero.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/13.
//
//

#ifndef Hero_h
#define Hero_h

#include "cocos2d.h"

class Hero : public cocos2d::Node
{
public:
    Hero();
    
    //公有属性
    bool isDead;
    bool isHurt;
    bool isJumping;
    bool isRunning;
    bool isAttacking;
    
    bool heroDirection;
    bool canCrazy;
    
    float currentHP;
    float totalHP;
    float currentMP;
    float totalMP;
    
    float percentage;
    float speed;
    
    void initHeroSprite(const char *heroName, int level);
    
    cocos2d::Sprite *getSprite();
    
    void setAnimation(const char *frameName, float delay, bool runDirection);
    void stopAnimation();
    
    void jumpUpAnimation(const char *frameName, float delay, bool runDirection);
    void jumpDownAnimation(const char *frameName, float delay, bool runDirection);
    void jumpEnd();
    
    void attackAnimation(const char *frameName, float delay, bool runDirection);
    void attackEnd();
    
    void deadAnimation(const char *frameName, float delay, bool runDirection);
    void deadEnd();
    
    void hurtByMonsterAnimation(const char *frameName, float delay, bool runDirection);
    void hurtByMonsterEnd();
    
    bool judgePosition(cocos2d::Size visibleSize);
    
    CREATE_FUNC(Hero);
    
private:
    cocos2d::Sprite *_heroSprite;
    const char *_heroName;
};

#endif /* Hero_h */
