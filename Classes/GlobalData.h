//
//  GlobalData.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/12/11.
//
//

#ifndef GlobalData_h
#define GlobalData_h

#include <iostream>
#include "cocos2d.h"

class Monster;

extern cocos2d::Vector<Monster*> gl_monsterOneList;
extern cocos2d::Vector<Monster*> gl_monsterTwoList;
extern cocos2d::Vector<Monster*> gl_monsterThreeList;
extern cocos2d::Vector<Monster*> gl_monsterFourList;
extern cocos2d::Vector<Monster*> gl_monsterFiveList;
extern cocos2d::Vector<Monster*> gl_monsterShowList;

extern bool gl_flag1;
extern bool gl_flag2;
extern bool gl_flag3;
extern bool gl_flag4;
extern bool gl_flag5;

inline void initGlobalFlags() {
    gl_flag1 = true;
    gl_flag2 = true;
    gl_flag3 = true;
    gl_flag4 = true;
    gl_flag5 = true;
}

static std::string gl_monsterName;
static std::string gl_monsterAttack;
static std::string gl_monsterWalk;
static std::string gl_monsterDie;
static std::string gl_monsterDieEnd;

//最大地图关数
#define MAPMAX 9
//当前选择的关卡
extern int gl_selectedGate;
//敌人种类
const static int gl_enemyType = 1;
//怪物名字
const static std::string gl_enemyName[gl_enemyType] = {"muzhuang"};
//怪物受伤动作名字
const static std::string gl_enemyHurt[gl_enemyType] = {"mzaHurt"};
//怪物站立动作帧图片名字
const static std::string gl_enemyStand[gl_enemyType] = {"mzStand"};
//怪物死亡动作名字
const static std::string gl_enemyDie[gl_enemyType] = {"mzDead"};
//怪物移动动作名字
const static std::string gl_enemyMove[gl_enemyType] = {"mzWalk"};
//怪物动作帧图片延时
const static float gl_enemyMoveDelay[gl_enemyType] = {0.0625};
//怪物移动动作帧图片数量
const static int gl_enemyMonvFrameCount[gl_enemyType] = {16};
//怪物攻击帧图片数量
const static int gl_enemyAttackFrameCount[gl_enemyType] = {11};
//怪物攻击帧图片延时
const static float gl_enemyAttackFrameDelay[gl_enemyType] = {0.1};
//怪物是否有武器
const static std::string gl_enemyBullet[gl_enemyType] = {"0"};  //0代表没有，1代表有
//怪物攻击能量
const static std::string gl_enemyPower[gl_enemyType] = {"50"};
//怪物血量
const static std::string gl_enemyBloods[gl_enemyType] = {"550"};
//怪物死亡后提供的经验
const static std::string gl_enemyExp[gl_enemyType] = {"200"};

#endif /* GlobalData_h */
