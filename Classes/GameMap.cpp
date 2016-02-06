//
//  GameMap.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/29.
//
//

#include "GameMap.h"
#include "GlobalDefine.h"
#include "Hero.h"

USING_NS_CC;

GameMap::GameMap()
{
    _map1 = nullptr;
    _map2 = nullptr;
    _map3 = nullptr;
}

GameMap::~GameMap()
{
    
}

void GameMap::initMap(const char *mapName1, const char *mapName2, const char *mapName3)
{
    _map1 = Sprite::createWithSpriteFrameName(mapName1);
    _map2 = Sprite::createWithSpriteFrameName(mapName2);
    _map3 = Sprite::createWithSpriteFrameName(mapName3);
    
    _map1->setAnchorPoint(Vec2(0, 0));
    _map2->setAnchorPoint(Vec2(0, 0));
    _map3->setAnchorPoint(Vec2(0, 0));
    
    _parallax = ParallaxNode::create();
    _parallax->addChild(_map1, 1, Vec2(1.18, 0), Vec2(0, 360));
    _parallax->addChild(_map2, 2, Vec2(1, 0), Vec2(0, 0));
    _parallax->addChild(_map3, 3, Vec2(0.7, 0), Vec2(0, 0));
    
    setAnchorPoint(Vec2(0, 0));
    addChild(_parallax);
}

void GameMap::moveMap(Hero *hero)
{
    if (hero->judgePosition(WINSIZE) && hero->heroDirection == false) {
        if (getPositionX() >= -(_map2->getContentSize().width - WINSIZE.width)) {
            setPosition(getPositionX() - hero->speed, getPositionY());
        }
    }
    if (hero->judgePosition(WINSIZE) && hero->heroDirection == true) {
        if (getPositionX() <= -10) {
            setPosition(getPositionX() + hero->speed, getPositionY());
        }
    }
}

bool GameMap::judgeMap(Hero *hero)
{
    if (getPositionX() >= -(_map2->getContentSize().width - WINSIZE.width) && hero->heroDirection  == false) {
        return false;
    }
    else if (getPositionX() <= -10 && hero->heroDirection == true) {
        return false;
    }
    else {
        return true;
    }
}