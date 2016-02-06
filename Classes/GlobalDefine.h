//
//  GlobalDefine.h
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/15.
//
//

#ifndef GlobalDefine_h
#define GlobalDefine_h

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#define     WINSIZE                       Director::getInstance()->getWinSize()

#define     setIntToXML                UserDefault::getInstance()->setIntegerForKey
#define     setFloatToXML            UserDefault::getInstance()->setFloatForKey
#define     setBoolToXML             UserDefault::getInstance()->setBoolForKey
#define     getIntFromXML           UserDefault::getInstance()->getIntegerForKey
#define     getFloatFromXML       UserDefault::getInstance()->getFloatForKey
#define     getBoolFromXML        UserDefault::getInstance()->getBoolForKey

#define     SOUND_KEY                   "soundClose"
#define     MUSIC_KEY                   "musicClose"
#define     SOUND_VOL                   "soundVolume"
#define     MUSIC_VOL                   "musicVolume"
#define     EXP_KEY                        "heroCurrentExp"
#define     GAME_LEVEL_KEY       "gameLevel"
#define     HERO_LEVEL_KEY         "heroLevel"
#define     HERO_COIN_KEY           "heroCoin"
#define     HERO_ENERGY_KEY     "heroEnergy"
#define     HERO_HP_KEY               "heroHP"
#define     HERO_MP_KEY              "heroMP"
#define     HERO_APOWER_KEY    "heroAPower"
#define     HERO_ABILITY_KEY     "heroAbility"
#define     SELECT_GATE                  "selectGate"
#define     GATE_ONE                        "gateOne"
#define     GATE_TWO                       "gateTwo"
#define     GATE_THREE                    "gateThree"
#define     GAME_OVER                    "gameOver"

#define     audioEngine                 SimpleAudioEngine::getInstance()

#define     PLAY_EFFECT     if (getBoolFromXML(SOUND_KEY)) { \
                                                    audioEngine->setEffectsVolume(getFloatFromXML(SOUND_VOL)); \
                                                    audioEngine->playEffect("Sound/button.wav"); \
                                                }

#endif /* GlobalDefine_h */
