//
//  HelpLayer.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/22.
//
//

#include "HelpLayer.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;

Scene *HelpLayer::createScene()
{
    Scene *scene = Scene::create();
    HelpLayer *layer = HelpLayer::create();
    scene->addChild(layer);
    return scene;
}

bool HelpLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("HelpScene.csb");
    
    Button *closeButton = rootNode->getChildByName<Button*>("closeButton");
    closeButton->addClickEventListener(CC_CALLBACK_0(HelpLayer::clickCloseButton, this));
    
    _text = rootNode->getChildByName<Text*>("text");
    rootNode->removeChildByName("text");
    
    DrawNode *area = DrawNode::create();
    Vec2 points[4] = {Vec2(0, 100), Vec2(500, 100), Vec2(500, 500), Vec2(0, 500)};
    area->drawPolygon(points, 4, Color4F(255, 255, 255, 255), 0.0f, Color4F(255, 255, 255, 255));
    
    ClippingNode *clipArea = ClippingNode::create();
    clipArea->setInverted(false);
    clipArea->setStencil(area);
    clipArea->addChild(_text);
    addChild(clipArea, 1);
    
    MoveBy *moveAct = MoveBy::create(7.0f, Vec2(0, 700));
    CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(HelpLayer::scrollBack, this));
    ActionInterval *action = Sequence::create(moveAct, callFunc, nullptr);
    _text->runAction(RepeatForever::create(action));
    
    addChild(rootNode);
    
    return true;
}

void HelpLayer::clickCloseButton()
{
    log("Close Help.");
    PLAY_EFFECT;
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, StartLayer::createScene()));
}

void HelpLayer::scrollBack()
{
    _text->setPosition(Vec2(260, 100));
}