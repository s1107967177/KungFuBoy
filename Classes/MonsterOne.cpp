//
//  MonsterOne.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/12/11.
//
//

#include "MonsterOne.h"
#include "GlobalData.h"
#include "Monster.h"
#include "Hero.h"
#include "GameMap.h"
#include "ActionTool.h"

USING_NS_CC;

MonsterOne *MonsterOne::createWithMapAndHero(GameMap *map, Hero *hero)
{
    MonsterOne *monsterOne = new MonsterOne();
    if (monsterOne && monsterOne->initMonster(map, hero)){
        monsterOne->autorelease();
    }
    else {
        CC_SAFE_DELETE(monsterOne);
    }
    return monsterOne;
}

bool MonsterOne::initMonster(GameMap *map, Hero *hero)
{
    _map = map;
    _hero = hero;
    
    initGlobalFlags();
    gl_monsterOneList.clear();
    gl_monsterTwoList.clear();
    gl_monsterThreeList.clear();
    gl_monsterShowList.clear();
    
    int gate = getIntFromXML(SELECT_GATE);
    std::string monsterType = "";
    switch (gate) {
        case 1:
            monsterType = "monster";
            break;
        case 2:
            monsterType = "lion";
            break;
        case 3:
            monsterType = "stone";
            break;
        default:
            break;
    }
    
    gl_monsterName = ActionTool::getLastFrameName((monsterType +"Walk").c_str());
    gl_monsterAttack = monsterType + "A";
    gl_monsterWalk = monsterType + "Walk";
    gl_monsterDie = monsterType + "Die";
    gl_monsterDieEnd = ActionTool::getLastFrameName((monsterType + "Die").c_str());
    
    log("%s", gl_monsterName.c_str());
    log("%s", gl_monsterAttack.c_str());
    
    auto monster1 = Monster::create();
    monster1->initMonsterSprite(gl_monsterName.c_str(), gl_monsterAttack.c_str(), gl_monsterWalk.c_str(), gl_monsterDie.c_str(), gl_monsterDieEnd.c_str(), 1);
    monster1->type = gate;
    monster1->setVisible(true);
    monster1->setPosition(1100, 365);
    _map->addChild(monster1);
    monster1->startListen(_hero, _map);
    gl_monsterShowList.pushBack(monster1);
    gl_flag1 = false;
    
    //第二波
    auto monster2 = Monster::create();
    monster2->initMonsterSprite(gl_monsterName.c_str(), gl_monsterAttack.c_str(), gl_monsterWalk.c_str(), gl_monsterDie.c_str(), gl_monsterDieEnd.c_str(), 1);
    monster2->type = gate;
    monster2->setVisible(false);
    monster2->setPosition(2000, 365);
    gl_monsterTwoList.pushBack(monster2);
    
    auto monster3 = Monster::create();
     monster3->initMonsterSprite(gl_monsterName.c_str(), gl_monsterAttack.c_str(), gl_monsterWalk.c_str(), gl_monsterDie.c_str(), gl_monsterDieEnd.c_str(), 1);
    monster3->type = gate;
    monster3->setVisible(false);
    monster3->setPosition(-150, 365);
    gl_monsterTwoList.pushBack(monster3);
    
    //第三波
    for (int i = 0; i < 3; ++i) {
        auto monster = Monster::create();
         monster->initMonsterSprite(gl_monsterName.c_str(), gl_monsterAttack.c_str(), gl_monsterWalk.c_str(), gl_monsterDie.c_str(), gl_monsterDieEnd.c_str(), 1);
        if (i == 0 || i == 1) {
            monster->setPosition(-100 * i, 365);
        }
        else {
            monster->setPosition(2000, 365);
        }
        monster->type = gate;
        monster->setVisible(false);
        gl_monsterThreeList.pushBack(monster);
    }
    schedule(schedule_selector(MonsterOne::updateMonster));
    return true;
}

void MonsterOne::updateMonster(float delta)
{
    //第二波
    if (gl_flag1 == false && gl_flag2 == true) {
        bool noMonster = true;
        for (auto monster : gl_monsterShowList) {
            if (!monster->isDead) {
                noMonster = false;
            }
        }
        if (noMonster) {
            scheduleOnce(schedule_selector(MonsterOne::showSecMon), 3.0f);
        }
    }
    //第三波
    if (gl_flag2 == false && gl_flag3 == true) {
        bool noMonster = true;
        for (auto monster : gl_monsterShowList) {
            if (!monster->isDead) {
                noMonster = false;
            }
        }
        if (noMonster) {
            scheduleOnce(schedule_selector(MonsterOne::showThrMon), 3.0f);
        }
    }
}

void MonsterOne::showSecMon(float delta)
{
    for (auto monster : gl_monsterTwoList) {
        monster->setVisible(true);
        _map->addChild(monster);
        monster->startListen(_hero, _map);
        gl_monsterShowList.pushBack(monster);
        gl_flag2 = false;
    }
}

void MonsterOne::showThrMon(float delta)
{
    for (auto monster : gl_monsterThreeList) {
        monster->setVisible(true);
        _map->addChild(monster);
        monster->startListen(_hero, _map);
        gl_monsterShowList.pushBack(monster);
        gl_flag3 = false;
    }
}