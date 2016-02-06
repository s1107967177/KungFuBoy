//
//  Hero.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/13.
//
//

#include "Hero.h"
#include "ActionTool.h"

USING_NS_CC;

Hero::Hero()
{
    isDead = false;
    isHurt = false;
    isJumping = false;
    isRunning = false;
    isAttacking = false;
    
    heroDirection = false;
    canCrazy = false;
    
    currentHP = totalHP = 0.0f;
    currentMP = 0.0f;
    totalMP = 100.0f;
    
    percentage = 100.0f;
    speed = 5;

    _heroName = nullptr;
    _heroSprite = nullptr;
}

void Hero::initHeroSprite(const char *heroName, int level)
{
    currentHP = totalHP = 300.0f * level;
    
    _heroName = heroName;
    _heroSprite = Sprite::createWithSpriteFrameName(_heroName);
    addChild(_heroSprite);
}

Sprite *Hero::getSprite() {
    return _heroSprite;
}

//设置动作
void Hero::setAnimation(const char *frameName, float delay, bool runDirection)
{
    if (heroDirection != runDirection) {
        heroDirection = runDirection;
        _heroSprite->setFlippedX(runDirection);
    }
    if (isRunning || isHurt || isAttacking) {
        return;
    }
    
    Animate *action = ActionTool::animationWithFrameName(frameName, delay);
    _heroSprite->runAction(RepeatForever::create(action));
    isRunning = true;
}

//停止动作
void Hero::stopAnimation()
{
    if (!isRunning) {
        return;
    }
    _heroSprite->stopAllActions();//当前精灵停止所有动画
    
    //恢复精灵原来的初始化贴图
    removeChild(_heroSprite, true);//把原来的精灵删掉
    _heroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_heroName));
    _heroSprite->setFlippedX(heroDirection);
    addChild(_heroSprite);
    isRunning = false;
}

//跳起
void Hero::jumpUpAnimation(const char *frameName, float delay, bool runDirection)
{
    //调整方向
    if (heroDirection != runDirection) {
        heroDirection = runDirection;
        _heroSprite->setFlippedX(runDirection);
    }
    if (isHurt || isAttacking) {
        return;
    }
    
    //创建动画动作
    Animate *action = ActionTool::animationWithFrameName(frameName, delay);
    _heroSprite->runAction(action);
    isJumping = true;
}

//跳落
void Hero::jumpDownAnimation(const char *frameName, float delay, bool runDirection)
{
    //调整方向
    if (heroDirection != runDirection) {
        heroDirection = runDirection;
    }
    if (isHurt || isAttacking) {
        return;
    }
    
    //创建动画动作
    Animate *action = ActionTool::animationWithFrameName(frameName, delay);
    _heroSprite->runAction(action);
    isJumping = true;
}

//跳完
void Hero::jumpEnd()
{
    _heroSprite->stopAllActions();//当前精灵停止所有动画
    
    //恢复原来的初始化贴图
    removeChild(_heroSprite);
    _heroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_heroName));
    _heroSprite->setFlippedX(heroDirection);
    addChild(_heroSprite);
    isJumping = false;
}

//攻击
void Hero::attackAnimation(const char *frameName, float delay, bool runDirection)
{
    //调整方向
    if (heroDirection != runDirection) {
        heroDirection = runDirection;
        _heroSprite->setFlippedX(runDirection);
    }
    if (isHurt || isAttacking) {
        return;
    }
    
    //创建动画动作
    Animate *action = ActionTool::animationWithFrameName(frameName, delay);
    //创建回调动作，攻击结束后调用attackEnd()
    CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(Hero::attackEnd, this));
    //创建连续动作
    ActionInterval *attackAction = Sequence::create(action, callFunc, nullptr);
    
    isAttacking = true;
    _heroSprite->runAction(attackAction);
}

//攻击结束
void Hero::attackEnd()
{
    _heroSprite->setFlippedX(heroDirection);
    isAttacking = false;
    if (canCrazy) {
        canCrazy = false;
        currentMP = 0;
    }
}

//受伤
void Hero::hurtByMonsterAnimation(const char *frameName, float delay, bool runDirection)
{
    if (isHurt || isDead) {
        return;
    }
    
    //受伤优先
    if (isRunning || isAttacking) {
        _heroSprite->stopAllActions();//当前精灵停止所有动画
        //恢复原来的初始化贴图
        removeChild(_heroSprite);//把原来的精灵删掉
        _heroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_heroName));
        _heroSprite->setFlippedX(runDirection);
        addChild(_heroSprite);
        isRunning = false;
        isAttacking = false;
    }
    
    //创建动画动作
    Animate *action = ActionTool::animationWithFrameName(frameName, delay);
    //创建回调动作，受伤结束调用hurtByMonsterEnd()
    CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(Hero::hurtByMonsterEnd, this));
    //创建连续动作
    ActionInterval *hurtAction = Sequence::create(action, callFunc, nullptr);
    _heroSprite->runAction(hurtAction);
    isHurt = true;
}

//受伤结束
void Hero::hurtByMonsterEnd()
{
    log("Hero Hurt!");
    currentHP -= 20.0f;
    isHurt = false;
    percentage = currentHP / totalHP * 100.0f;
    if (currentHP < 0.0f) {
        deadAnimation("dead", 0, heroDirection);
    }
}

//死亡
void Hero::deadAnimation(const char *frameName, float delay, bool runDirection)
{
    _heroSprite->stopAllActions();
    //调整方向
    if (heroDirection != runDirection) {
        _heroSprite->setFlippedX(runDirection);
    }
    //创建动作
    Animate *action = ActionTool::animationWithFrameName(frameName, delay);
    //创建回调动作，受伤结束调用deadEnd()
    CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(Hero::deadEnd, this));
    //创建连续动作
    ActionInterval *deadAction = Sequence::create(action, callFunc, nullptr);
    _heroSprite->runAction(deadAction);
    isDead = true;
}

//死亡结束
void Hero::deadEnd()
{
    isDead = true;
    //恢复死亡的样子
    removeChild(_heroSprite);
    _heroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_heroName));
    addChild(_heroSprite);
}

bool Hero::judgePosition(Size visibleSize)
{
    if (this->getPositionX() > (visibleSize.width / 2.0 + 2.0) || (this->getPositionX() < visibleSize.width / 2.0 - 2.0)) //精灵不在中间位置
        return false;
    else
        return true;//到达中间位置
}
