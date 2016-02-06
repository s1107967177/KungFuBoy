//
//  MijiLayer.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/17.
//
//

#include "MijiLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene *MijiLayer::createScene()
{
    Scene *scene = Scene::create();
    MijiLayer *layer = MijiLayer::create();
    scene->addChild(layer);
    return scene;
}

bool MijiLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    leftFlag =  rightFlag = false;
    
    auto rootNode = CSLoader::createNode("MijiScene.csb");    
    spriteBG = rootNode->getChildByName<Sprite*>("spriteBG");
    interface_1 = spriteBG->getChildByName<Sprite*>("interface_1");
    interface_2 = spriteBG->getChildByName<Sprite*>("interface_2");
    
    auto closeButton = spriteBG->getChildByName<ui::Button*>("closeButton");
    closeButton->addClickEventListener(CC_CALLBACK_0(MijiLayer::clickCloseButton, this));
    
    auto leftButton = spriteBG->getChildByName<ui::Button*>("nextLeftButton");
    leftButton->addClickEventListener(CC_CALLBACK_0(MijiLayer::clickNextLeftButton, this));
    
    auto rightButton = spriteBG->getChildByName<ui::Button*>("nextRightButton");
    rightButton->addClickEventListener(CC_CALLBACK_0(MijiLayer::clickNextRightButton, this));
    
    addChild(rootNode);
    
    return true;
}

void MijiLayer::clickCloseButton()
{
    log("Close Miji.");
    PLAY_EFFECT;
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, StartLayer::createScene()));
}

void MijiLayer::clickNextLeftButton()
{
    log("Page turn left.");
    PLAY_EFFECT;
    if (interface_2->isVisible() == false && leftFlag == false) { //在中间
        interface_2->setVisible(true);
        leftFlag = true;
    } else if(interface_2->isVisible() == true && leftFlag == false) { //在最右边
        interface_2->setVisible(false);
        rightFlag = false;
    }
}

void MijiLayer::clickNextRightButton()
{
    log("Page turn right.");
    PLAY_EFFECT;
    if (interface_2->isVisible() == false && rightFlag == false) { //在中间
        interface_2->setVisible(true);
        rightFlag = true;
    } else if (interface_2->isVisible() == true && rightFlag == false){ //在最左边
        interface_2->setVisible(false);
        leftFlag = false;
    }
}