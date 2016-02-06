//
//  MonsterOne.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/12/11.
//
//

#ifndef MonsterOne_h
#define MonsterOne_h

#include "GlobalDefine.h"

class Monster;
class Hero;
class GameMap;

class MonsterOne : public cocos2d::Node
{
public:
    void updateMonster(float delta);
    void showSecMon(float delta);
    void showThrMon(float delta);
    static MonsterOne *createWithMapAndHero(GameMap *map, Hero *hero);
    bool initMonster(GameMap *map, Hero *hero);
    
private:
    GameMap *_map;
    Hero *_hero;
};

#endif /* MonsterOne_h */
