//
//  TujiLayer.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/18.
//
//

#include "TujiLayer.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;

Scene *TujiLayer::createScene()
{
    Scene *scene = Scene::create();
    TujiLayer *layer = TujiLayer::create();
    scene->addChild(layer);
    return scene;
}

bool TujiLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("TujiScene.csb");
    
    Sprite* bgSprite = rootNode->getChildByName<Sprite*>("bgSprite");
    
    _mzPic = bgSprite->getChildByName<Sprite*>("mzPic");
    _mzText = bgSprite->getChildByName<Sprite*>("mzText");
    _mzLabel = bgSprite->getChildByName<Text*>("mzLabel");
    _lionPic = bgSprite->getChildByName<Sprite*>("lionPic");
    _lionLabel = bgSprite->getChildByName<Text*>("lionLabel");
    _stonePic = bgSprite->getChildByName<Sprite*>("stonePic");
    _stoneLabel = bgSprite->getChildByName<Text*>("stoneLabel");
    
    Button *closeButton = bgSprite->getChildByName<ui::Button*>("closeButton");
    closeButton->addClickEventListener(CC_CALLBACK_0(TujiLayer::clickCloseButton, this));
    
    _listView = rootNode->getChildByName<ListView*>("ListView_1");
    _listView->addEventListener(CC_CALLBACK_2(TujiLayer::selectedItemEvent, this));
    addChild(rootNode);
    
    return true;
}

void TujiLayer::clickCloseButton()
{
    log("Close Tuji.");
    PLAY_EFFECT;
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, StartLayer::createScene()));
}

void TujiLayer::selectedItemEvent(Ref *pSender, ListView::EventType type)
{
    ListView *listView = static_cast<ListView*>(pSender);
    
    if (type == ListView::EventType::ON_SELECTED_ITEM_END) {
        PLAY_EFFECT;
        switch(listView->getCurSelectedIndex())
        {
            case Mz:
                log("This is mz monster.");
                _mzPic->setVisible(true);
                _mzText->setVisible(true);
                _mzLabel->setVisible(true);
                _lionPic->setVisible(false);
                _lionLabel->setVisible(false);
                _stonePic->setVisible(false);
                _stoneLabel->setVisible(false);
                break;
            case Lion:
                log("This is lion monster.");
                _mzPic->setVisible(false);
                _mzText->setVisible(false);
                _mzLabel->setVisible(false);
                _lionPic->setVisible(true);
                _lionLabel->setVisible(true);
                _stonePic->setVisible(false);
                _stoneLabel->setVisible(false);
                break;
            case Stone:
                log("This is stone monster.");
                _mzPic->setVisible(false);
                _mzText->setVisible(false);
                _mzLabel->setVisible(false);
                _lionPic->setVisible(false);
                _lionLabel->setVisible(false);
                _stonePic->setVisible(true);
                _stoneLabel->setVisible(true);
                break;
            case Unknown:
                log("This is unknown monster.");
                _mzPic->setVisible(false);
                _mzText->setVisible(false);
                _mzLabel->setVisible(false);
                _lionPic->setVisible(false);
                _lionLabel->setVisible(false);
                _stonePic->setVisible(false);
                _stoneLabel->setVisible(false);
                break;
            default:
                break;
        }
    } // end_of_if
}