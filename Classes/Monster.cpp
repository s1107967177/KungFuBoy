//
//  Monster.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/14.
//
//

#include "Monster.h"
#include "ActionTool.h"
#include "Hero.h"
#include "GameMap.h"

USING_NS_CC;

Monster::Monster()
{
    type = 0;
    isRunning = false;
    isAttacking = false;
    isHurt = false;
    isDead = false;
    monsterDirection = false;

    _monsterSprite = nullptr;
    _monsterName = nullptr;
    _monsterAttack = nullptr;
    _monsterWalk = nullptr;
    _monsterDie = nullptr;
    _dieName = nullptr;
    
    _myHero = nullptr;
    _myMap = nullptr;
    _myDisToHero = 0.0f;
    _myHP = 0;
}

void Monster::initMonsterSprite(const char *name, const char *attack, const char *walk,
                                                          const char *die, const char *dieLast, int level)
{
    _monsterName = name;
    _monsterAttack = attack;
    _monsterWalk = walk;
    _monsterDie = die;
    _dieName = dieLast;
    _myHP = 100 * (1 + 0.3 * level);
    _monsterSprite = Sprite::createWithSpriteFrameName(_monsterName);
    addChild(_monsterSprite);
}

Sprite *Monster::getSprite()
{
    return _monsterSprite;
}

void Monster::setAnimation(const char *frameName, bool runDirection, float delay, int num)
{
    if (monsterDirection != runDirection) {
        monsterDirection = runDirection;
        _monsterSprite->setFlippedX(runDirection);
    }
    
    if (isRunning || isAttacking || isHurt || isDead) {
        return;
    }
    
    Animate *action = ActionTool::animationWithFrameName(frameName, delay);
    _monsterSprite->runAction(RepeatForever::create(action));
    isRunning = true;
}

void Monster::stopAnimation()
{
    if (!isRunning) {
        return;
    }
    
    _monsterSprite->stopAllActions();//当前精灵停止所有动画
    //恢复精灵原来的初始化贴图
    removeChild(_monsterSprite, true);
    _monsterSprite = Sprite::createWithSpriteFrameName(_monsterName);
    _monsterSprite->setFlippedX(monsterDirection);
    addChild(_monsterSprite);
    isRunning = false;
}

//攻击
void Monster::attackAnimation(const char *frameName, bool runDirection, float delay, int num)
{
    if (isRunning || isAttacking || isHurt || isDead) {
        return;
    }
    Animate *action = ActionTool::animationWithFrameName(frameName, delay);
    CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(Monster::attackEnd, this));
    _monsterSprite->runAction(Sequence::create(action, callFunc, nullptr));
    isAttacking = true;
}
//攻击结束
void Monster::attackEnd()
{
    removeChild(_monsterSprite);
    _monsterSprite = Sprite::createWithSpriteFrameName(_monsterName);
    _monsterSprite->setFlippedX(monsterDirection);
    addChild(_monsterSprite);
    isAttacking = false;
}

//受伤
void Monster::hurtAnimation(const char *frameName, bool runDirection, float delay, int num)
{
    if (isHurt || isDead) {
        return;
    }
    //受伤优先
    if (isRunning || isAttacking) {
        _monsterSprite->stopAllActions();
        removeChild(_monsterSprite);
        _monsterSprite = Sprite::createWithSpriteFrameName(_monsterName);
        addChild(_monsterSprite);
        isRunning = false;
        isAttacking = false;
    }
    Animate *action = ActionTool::animationWithFrameName(frameName, delay);
    CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(Monster::hurtEnd, this));
    _monsterSprite->runAction(Sequence::create(action, callFunc, nullptr));
    isHurt = true;
}
//受伤结束
void Monster::hurtEnd()
{
    log("Monster hurt!");
    isHurt = false;
    if (_myHero->canCrazy) {
        _myHP -= 100;
    } else {
        _myHP -= 30;
    }
    
    if (_myHP <= 0) {
        //播放怪物死亡
        deadAnimation(_monsterDie, monsterDirection, 0.1f, 0);
    }
}

//死亡
void Monster::deadAnimation(const char *frameName, bool runDirection, float delay, int num)
{
    isDead = true;
    //创建动作
    Animate *action = ActionTool::animationWithFrameName(frameName, delay);
    CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(Monster::deadEnd, this));
    _monsterSprite->runAction(Sequence::create(action, callFunc, nullptr));
    if (_myHero->currentMP < 100) {
        _myHero->currentMP = _myHero->currentMP + 50;
        if (_myHero->currentMP > 100) {
            _myHero->currentMP = 100;
        }
    }
}
//死亡结束
void Monster::deadEnd()
{
    //恢复死亡的样子
    removeChild(_monsterSprite);
    _monsterSprite = Sprite::createWithSpriteFrameName(_dieName);
    _monsterSprite->setFlippedX(monsterDirection);
    addChild(_monsterSprite);
    //怪物闪下再死亡
    Blink *blinkAction = Blink::create(2, 3);//两秒钟闪3下
    CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(Monster::blinkEnd, this));
    _monsterSprite->runAction(Sequence::create(blinkAction, callFunc, nullptr));
}

void Monster::blinkEnd()
{
    removeAllChildren();
}

void Monster::followRun(Hero *myHero, GameMap *myMap)
{
    //得到两点x距离，记得怪物的坐标要加上地图的
    float x = _myHero->getPositionX() - (this->getPositionX() + _myMap->getPositionX());
    
    //先计算怪物与英雄的距离
    _myDisToHero = fabs(x);
    
    if (x > HATE_RANGE) {     //当怪物与英雄的距离超过1280
        return;
    }
    if (_myDisToHero <= ATTACK_RANGE) {      //在怪物攻击范围内，怪物停止移动
        stopAnimation();
        scheduleOnce(schedule_selector(Monster::judgeAttack), 2.5f);
        return;
    }
    
    if (x < -100) {
        monsterDirection = false;
        _monsterSprite->setFlippedX(monsterDirection);
        if (isAttacking) {
            return;
        }
        setAnimation(_monsterWalk, monsterDirection, 0.1f, 0);
        setPosition(getPositionX() - 1.5, getPositionY());
    }
    else if (x > 100) {
        monsterDirection = true;
        _monsterSprite->setFlippedX(monsterDirection);
        if (isAttacking) {
            return;
        }
        setAnimation(_monsterWalk, monsterDirection, 0.1f, 0);
        setPosition(getPositionX() + 1.5, getPositionY());
    }
}

void Monster::judgeAttack(float delta)
{
    attackAnimation(_monsterAttack, monsterDirection, 0.08f, 0);
}

//启动监听
void Monster::startListen(Hero *myHero, GameMap *myMap)
{
    _myHero = myHero;
    _myMap = myMap;
    schedule(schedule_selector(Monster::updateMonster), 1.0f);  //每隔一秒计算距离
    scheduleUpdate();   //英雄一旦进入可视范围，怪物追着英雄打
}

//监听函数，每隔一秒检测下
void Monster::updateMonster(float delta)
{
    if (isDead || _myHero->isDead) {
        return;
    }
    float x = _myHero->getPositionX() - (this->getPositionX() + _myMap->getPositionX());
    _myDisToHero = fabs(x);
}

void Monster::update(float delta)
{
    if (isDead || _myHero->isDead) {
        return;
    }
    if (_myDisToHero < HATE_RANGE && _myHero->isDead == false) {
        followRun(_myHero, _myMap);
    }
}
