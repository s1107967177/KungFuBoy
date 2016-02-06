//
//  GameMap.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/14.
//
//

#ifndef GameMap_h
#define GameMap_h

#include "cocos2d.h"

class Hero;

class GameMap : public cocos2d::Node
{
public:
    GameMap();
    virtual ~GameMap();
    //初始化地图
    void initMap(const char *mapName1, const char *mapName2, const char *mapName3);
    //根据精灵的位置移动地图
    void moveMap(Hero *hero);
    //判断地图是否到达边缘
    bool judgeMap(Hero *hero);
    
    CREATE_FUNC(GameMap);

private:
    cocos2d::Sprite *_map1;
    cocos2d::Sprite *_map2;
    cocos2d::Sprite *_map3;
    
    cocos2d::ParallaxNode *_parallax;
};

#endif /* GameMap_h */
