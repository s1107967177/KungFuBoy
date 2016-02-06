//
//  Monster.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/14.
//
//

#ifndef Monster_h
#define Monster_h

#include "cocos2d.h"

#define ATTACK_RANGE 120
#define HATE_RANGE      1280

class Hero;
class GameMap;

class Monster : public cocos2d::Node
{
public:
    Monster();
    
    //公有属性
    int  type;
    bool isRunning;
    bool isAttacking;
    bool isHurt;
    bool isDead;
    bool monsterDirection;
    
    //方法
    //创建不带血条的怪物
    void initMonsterSprite(const char *name, const char *attack, const char* walk,
                                             const char *die, const  char *dieLast, int level);
    //返回英雄
    cocos2d::Sprite *getSprite();
    
    void setAnimation(const char *frameName, bool runDirection, float delay, int num);
    void stopAnimation();
    
    void attackAnimation(const char *frameName, bool runDirection, float delay, int num);
    void attackEnd();
    
    void hurtAnimation(const char *frameName, bool runDirection, float delay, int num);
    void hurtEnd();
    
    void deadAnimation(const char *frameName, bool runDirection, float delay, int num);
    void deadEnd();
    
    //怪物死亡闪烁结束
    void blinkEnd();
    
    //在可视范围内怪物跟随英雄运动
    void followRun(Hero *myHero, GameMap *myMap);
    //判断攻击
    void judgeAttack(float delta);
    
    //怪物启动监听英雄
    void startListen(Hero *myHero, GameMap *myMap);
    //监听函数，每隔3秒检测下，计算英雄与怪物的距离
    void updateMonster(float delta);
    //更新函数，如果英雄在可视范围内，不断触发
    void update(float delta);
    
    CREATE_FUNC(Monster);
    
private:
    cocos2d::Sprite *_monsterSprite;
    const char *_monsterName;
    const char *_monsterAttack;
    const char *_monsterWalk;
    const char *_monsterDie;
    const char *_dieName;
    
    Hero *_myHero;
    GameMap *_myMap;
    float _myDisToHero;
    int _myHP;
};

#endif /* Monster_h */
