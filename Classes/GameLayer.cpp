//
//  GameLayer.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/29.
//
//

#include "GameLayer.h"
#include "GameMap.h"
#include "GateMapLayer.h"
#include "Hero.h"
#include "Monster.h"
#include "MonsterOne.h"
#include "PauseLayer.h"
#include "GlobalData.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;
using namespace cocos2d::extension;

cocos2d::Scene *GameLayer::createScene()
{
    Scene *scene = Scene::create();
    GameLayer *layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

void GameLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    if (getBoolFromXML(MUSIC_KEY)) {
        if (audioEngine->isBackgroundMusicPlaying() == false) {
            audioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSIC_VOL));
            audioEngine->playBackgroundMusic("Sound/gameBGM.wav", true);
        }
    } else {
        audioEngine->pauseBackgroundMusic();
    }
}

bool GameLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    //资源
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/mapBefore.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/mapBg.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/mapRoad.plist");
    
    //初始化
    _velocity = 10.0;
    _runDirection = false;
    _isJumping = false;
    _isRunning = false;
    
    _selectedGate = getIntFromXML(SELECT_GATE);
    __String *bgName = __String::createWithFormat("bgmap%d.png", _selectedGate);
    __String *midName = __String::createWithFormat("MapMiddle%d.png", _selectedGate);
    __String *groundName = __String::createWithFormat("MapGround%d.png", _selectedGate);
    __String *beforeName = __String::createWithFormat("MapBefore%d.png", _selectedGate);
    __String *comboBtnName = __String::createWithFormat("comboButton%d", _selectedGate);

    log("%s", bgName->getCString());
    Sprite *bgPic = Sprite::createWithSpriteFrame(
            SpriteFrameCache::getInstance()->getSpriteFrameByName(bgName->getCString()));
    bgPic->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
    addChild(bgPic, 0);
    
    _myMap = GameMap::create();
    _myMap->initMap(
                    midName->getCString(), groundName->getCString(), beforeName->getCString());
    addChild(_myMap, 1);
    
    auto rootNode = CSLoader::createNode("GameScene.csb");
    addChild(rootNode, 2);
    
    Sprite *barGround = rootNode->getChildByName<Sprite*>("barGround");
    _hpBar = barGround->getChildByName<LoadingBar*>("hpBar");
    _mpBar = barGround->getChildByName<LoadingBar*>("mpBar");
    
    Sprite *quanSprite = rootNode->getChildByName<Sprite*>("quanSprite");
    Button *fistButton = quanSprite->getChildByName<Button*>("fistButton");
    fistButton->addClickEventListener(CC_CALLBACK_0(GameLayer::fistAttack, this));
    
    Sprite *jiaoSprite = rootNode->getChildByName<Sprite*>("jiaoSprite");
    Button *footButton = jiaoSprite->getChildByName<Button*>("footButton");
    footButton->addClickEventListener(CC_CALLBACK_0(GameLayer::footAttack, this));
    
    _comboSprite = rootNode->getChildByName<Sprite*>("comboSprite");
    _comboSprite->setVisible(false);
    auto comboButtonVec = _comboSprite->getChildren();
    for (auto node : comboButtonVec) {
        Button *selectedButton = static_cast<Button*>(node);
        if(selectedButton->getName() == std::string(comboBtnName->getCString())) {
           selectedButton->setVisible(true);
           selectedButton->addClickEventListener(CC_CALLBACK_0(GameLayer::comboAttack, this));
        }
        else {
            selectedButton->setVisible(false);
        }
    }
    
    Sprite *tiaoSprite = rootNode->getChildByName<Sprite*>("tiaoSprite");
    Button *jumpButton = tiaoSprite->getChildByName<Button*>("jumpButton");
    jumpButton->addClickEventListener(CC_CALLBACK_0(GameLayer::jump, this));
    
    Button *pauseButton = rootNode->getChildByName<Button*>("pauseButton");
    pauseButton->addClickEventListener(CC_CALLBACK_0(GameLayer::gamePause, this));
    
    auto backwardBG = Scale9Sprite::createWithSpriteFrameName("directionNormal.png");
    auto backwardSelBG = Scale9Sprite::createWithSpriteFrameName("directionSelected.png");
    auto backwardBtn = ControlButton::create(backwardBG);
    backwardBtn->setBackgroundSpriteForState(backwardSelBG, Control::State::HIGH_LIGHTED);
    backwardBtn->setZoomOnTouchDown(false);
    backwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::backward), Control::EventType::TOUCH_DOWN);
    backwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::backward), Control::EventType::TOUCH_UP_INSIDE);
    backwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::backward), Control::EventType::DRAG_OUTSIDE);
    backwardBtn->setPreferredSize(Sprite::createWithSpriteFrameName("directionNormal.png")->getContentSize());
    
    auto forwardBG = Scale9Sprite::createWithSpriteFrameName("directForNor.png");
    auto forwardSelBG = Scale9Sprite::createWithSpriteFrameName("directForSel.png");
    auto forwardBtn = ControlButton::create(forwardBG);
    forwardBtn->setBackgroundSpriteForState(forwardSelBG, Control::State::HIGH_LIGHTED);
    forwardBtn->setZoomOnTouchDown(false);
    forwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::forward), Control::EventType::TOUCH_DOWN);
    forwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::forward), Control::EventType::TOUCH_UP_INSIDE);
    forwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::forward), Control::EventType::DRAG_OUTSIDE);
    forwardBtn->setPreferredSize(Sprite::createWithSpriteFrameName("directForNor.png")->getContentSize());
    
    backwardBtn->setPosition(117, 70);
    forwardBtn->setPosition(304, 70);
    
    addChild(backwardBtn, 2);
    addChild(forwardBtn, 2);
    
    _hero = Hero::create();
    _hero->initHeroSprite("idle.png", 1);
    _hero->setPosition(100, 360);
    addChild(_hero, 3);
    
    MonsterOne *monster = MonsterOne::createWithMapAndHero(_myMap, _hero);
    addChild(monster);
    
    schedule(schedule_selector(GameLayer::update), 1.0f / 60);
    return true;
}

void GameLayer::forward(Ref *pSender, Control::EventType type)
{
    if (_hero->isJumping && _hero->isAttacking) {
        return;
    }
    switch (type) {
        case Control::EventType::TOUCH_DOWN:
            _isRunning = true;
            _runDirection = false;
            break;
        case Control::EventType::TOUCH_UP_INSIDE:
            _isRunning = false;
            _hero->stopAnimation();
            break;
        case Control::EventType::DRAG_OUTSIDE:
            _isRunning = false;
            _hero->stopAnimation();
            break;
        default:
            break;
    }

}

void GameLayer::backward(Ref *pSender, Control::EventType type)
{
    if (_hero->isJumping && _hero->isAttacking) {
        return;
    }
    switch (type) {
        case Control::EventType::TOUCH_DOWN:
            _isRunning = true;
            _runDirection = true;
            break;
        case Control::EventType::TOUCH_UP_INSIDE:
            _isRunning = false;
            _hero->stopAnimation();
            break;
        case Control::EventType::DRAG_OUTSIDE:
            _isRunning = false;
            _hero->stopAnimation();
            break;
        default:
            break;
    }
}

void GameLayer::gamePause()
{
    PLAY_EFFECT;
    //RenderTexture是一个纹理渲染类，我们要把要渲染的当前场景放进去，这是初始化它的大小
    _render = RenderTexture::create(WINSIZE.width, WINSIZE.height);
    //开始获取内容
    _render->begin();
    //是用结点的visit方法加入到渲染中
    Director::getInstance()->getRunningScene()->visit();
    //结束
    _render->end();
    _render->retain();
    
    //截屏需要在截完屏的下一帧才能处理RenderTexture
    auto _schedule = getScheduler();
    auto pushScene = [&](float tm) {
        Director::getInstance()->pushScene(PauseLayer::createScene(_render));
    };
    _schedule->schedule(pushScene, this, 0.0f, 0, 0.0f, false, "screenshot");
}

void GameLayer::fistAttack()
{
     PLAY_EFFECT;
    if (_hero->isRunning || _hero->isAttacking || _hero->isHurt || _hero->isJumping) {
        return;
    }
    _hero->attackAnimation("fist", 0.1f, _hero->heroDirection);
    log("Fist attack!");
}

void GameLayer::footAttack()
{
    PLAY_EFFECT;
    if (_hero->isRunning || _hero->isAttacking || _hero->isHurt || _hero->isJumping) {
        return;
    }
    _hero->attackAnimation("leg", 0.1f, _hero->heroDirection);
    log("Foot attack!");
}

void GameLayer::comboAttack()
{
    PLAY_EFFECT;
    if (_hero->isRunning || _hero->isAttacking || _hero->isHurt || _hero->isJumping) {
        return;
    }
    if (getBoolFromXML(SOUND_KEY)) {
        audioEngine->setEffectsVolume(getFloatFromXML(SOUND_VOL));
        audioEngine->playEffect("Sound/combo.wav");
    }
    _hero->canCrazy = true;
    switch (_selectedGate) {
        case 1:
            _hero->attackAnimation("combo", 0.1, _hero->heroDirection);
            break;
        case 2:
            _hero->attackAnimation("bakandao", 0.1, _hero->heroDirection);
            break;
        case 3:
            _hero->attackAnimation("gun", 0.1, _hero->heroDirection);
        default:
            break;
    }
    log("Combo attack%d", _selectedGate);
}

void GameLayer::jump()
{
    PLAY_EFFECT;
    if (_hero->isRunning || _hero->isAttacking || _hero->isHurt || _hero->isJumping) {
        return;
    }
    if (getBoolFromXML(SOUND_KEY)) {
        audioEngine->setEffectsVolume(getFloatFromXML(SOUND_VOL));
        audioEngine->playEffect("Sound/Jump.wav");
    }
    _isJumping = true;
}

#define MOVE_HERO \
    _hero->setPosition(_hero->getPositionX() + _hero->speed, _hero->getPositionY() + _velocity)

#define UNMOVE_HERO \
    _hero->setPosition(_hero->getPositionX() , _hero->getPositionY() + _velocity)

#define HERO_IN_REDGE \
    (_hero->getPositionX() <= WINSIZE.width - 8)

#define HERO_IN_LEDGE \
    (_hero->getPositionX() >= 8)

//精灵没到达窗口中间位置或者地图已经移动到边缘了，精灵才可以移动，否则只播放动画
#define HERO_MOVEABLE \
    (!_hero->judgePosition(WINSIZE) || _myMap->judgeMap(_hero))

void GameLayer::moveXWhileJumping()
{
    if (_hero->heroDirection == false) {
        if (HERO_IN_REDGE) { //不让精灵超出右边
            if (HERO_MOVEABLE) {
                MOVE_HERO;
            }
            else {
                UNMOVE_HERO;
            }
            _myMap->moveMap(_hero);
        }
        else {
            UNMOVE_HERO;
        }
    }
    else {
        if (HERO_IN_LEDGE) { //不让精灵超出左边
            if (HERO_MOVEABLE) {
                MOVE_HERO;
            }
            else {
                UNMOVE_HERO;
            }
            _myMap->moveMap(_hero);
        }
        else {
            UNMOVE_HERO;
        }
    }
}

bool GameLayer::isAttackingMonster(Hero *hero, Monster *monster)
{
    float hero_x = hero->getPositionX();
    float monster_x = monster->getPositionX() + _myMap->getPositionX();
    if (hero->heroDirection) {
        if (monster_x <= hero_x) {
            return true;
        }
    }
    else {
        if (monster_x >= hero_x) {
            return true;
        }
    }
    return false;
}

void GameLayer::gameOver()
{
    
}

void GameLayer::gameVictory()
{
    if (getBoolFromXML(MUSIC_KEY)) {
        
    }
}

void GameLayer::update(float delta)
{
    //人物跳起
    if (_isJumping) {
        _velocity -= 0.3;
        if (_velocity > 0.1) {
            _hero->jumpUpAnimation("jumpup", 0.1, _runDirection);
            moveXWhileJumping();
        }
        else {
            _hero->jumpDownAnimation("jumpdown", 0.1, _runDirection);
            moveXWhileJumping();
        }
        if (_hero->getPositionY() <= 359) {
            _hero->jumpEnd();
            _hero->setPosition(_hero->getPositionX(), 360);
            _velocity = 10.0;
            _isJumping = false;
        }
    }

    //人物移动
    if (_isRunning && _runDirection == false && _hero->isHurt == false && _hero->isAttacking == false && _hero->isJumping == false) {
        _hero->setAnimation("run", 0.07, _runDirection);
        if (HERO_IN_REDGE) {
            if (HERO_MOVEABLE) {
                _hero->setPosition(_hero->getPositionX() + _hero->speed, _hero->getPositionY());
            }
            _myMap->moveMap(_hero);
        }
    }
    else if (_isRunning && _runDirection == true && _hero->isHurt == false && _hero->isAttacking == false && _hero->isJumping == false) {
        _hero->setAnimation("run", 0.07, _runDirection);
        if (HERO_IN_LEDGE) {
            if (HERO_MOVEABLE) {
                _hero->setPosition(_hero->getPositionX() - _hero->speed, _hero->getPositionY());
            }
            _myMap->moveMap(_hero);
        }
    }

    //主角和怪物攻击碰撞检测
    if (_hero->isAttacking) {
        for (auto monster : gl_monsterShowList) {
            //怪物没死
            if (monster->isDead == false && isAttackingMonster(_hero, monster) && _hero->isJumping == false) {
                float x = _hero->getPositionX() - (monster->getPositionX() + _myMap->getPositionX());
                auto dis = fabs(x);
                if (dis <= 150) {
                    if (monster->type == 1) {
                        monster->hurtAnimation("monsterHurt", monster->monsterDirection, 0.2f, 1);
                    }
                    else if (monster->type == 2) {
                        monster->hurtAnimation("lionHurt", monster->monsterDirection, 0.2f, 1);
                    }
                    else {
                        monster->hurtAnimation("stoneHurt", monster->monsterDirection, 0.2, 1);
                    }
                }
            }
        }
    }
    
    for (auto monster : gl_monsterShowList) {
        if (!monster->isDead) {
            if (monster->isAttacking && _hero->isDead == false && _hero->isJumping == false) {
                float x = _hero->getPositionX() - (monster->getPositionX() + _myMap->getPositionX());
                auto dis = fabs(x);
                if (dis <= 130) {
                    _hero->hurtByMonsterAnimation("hurt", 0.2f, _runDirection);
                    _hpBar->setPercent(_hero->percentage);
                }
            }
        }
    }
    _mpBar->setPercent(_hero->currentMP);
    if (_mpBar->getPercent() >= 100) {      //MP满则可放大招
        _comboSprite->setVisible(true);
    }
    else {
        _comboSprite->setVisible(false);
    }
}
