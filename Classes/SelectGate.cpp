//
//  SelectGate.cpp
//  KungFuBoy
//
//  Created by 唐家琪 on 15/11/24.
//
//

#include "SelectGate.h"
#include <math.h>

#define     PI                                              acos(-1)
#define     MENU_SCALE                        0.3              //菜单的缩小比例，最小比例是1-MENU_SCALE
#define     MENU_ASLOPE                      60.0           //菜单的倾斜度
#define     CALC_A                                  1                 //calcFunction(x)    x/(x+a), 其中a为常数
#define     ANIMATION_DURATION      0.3              //动画运行时间

//菜单项大小与屏幕大小的比例，可以通过setContentSize设置
#define     CONTENT_SIZE_SCALE       (2.0/3)
//菜单项长度与屏幕长度的比例，滑动一个菜单项长度，菜单项变化一个
#define     ITEM_SIZE_SCALE              (1.0/4)

USING_NS_CC;

bool SelectGate::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    _index = 0;
    _lastIndex = 0;
    ignoreAnchorPointForPosition(false);
    _selectedItem = nullptr;
    
    auto size = Director::getInstance()->getWinSize();
    setContentSize(size * CONTENT_SIZE_SCALE);
    setAnchorPoint(Point(0.5f, 0.5f));
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(SelectGate::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SelectGate::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SelectGate::onTouchEnded, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void SelectGate::addMenuItem(cocos2d::MenuItem *item)
{
    item->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
    addChild(item);
    _items.pushBack(item);
    reset();
    //如果希望开始没有移动效果，改成updatePosition函数即可
    updatePositionWithAnimation();
    return;
}

void SelectGate::updatePosition()
{
    auto menuSize = getContentSize();
    for (int i = 0; i < _items.size(); ++i) {
        //设置位置
        float x = calcFunction(i - _index, menuSize.width / 2);
        _items.at(i)->setPosition(Vec2(menuSize.width / 2 + x, menuSize.height / 2));
        //设置zOrder，即绘制顺序
        _items.at(i)->setZOrder(-std::abs(i - _index) * 100);
        //设置伸缩比例
        _items.at(i)->setScale(1.0 - std::abs(calcFunction(i - _index, MENU_SCALE)));
        //设置倾倒，Node没有setCamera函数, 将OrbitCamera的运行时间设为0来达到效果
        auto orbit1 = OrbitCamera::create(0, 1, 0, calcFunction(i - _lastIndex, MENU_ASLOPE), calcFunction(i - _lastIndex, MENU_ASLOPE), 0, 0);
        _items.at(i)->runAction(orbit1);
    }
    return;
}

void SelectGate::updatePositionWithAnimation()
{
    //先停止所有可能存在的动作
    for (ssize_t i = 0; i < _items.size(); ++i) {
        _items.at(i)->stopAllActions();
    }
    auto menuSize = getContentSize();
    for (ssize_t i = 0; i < _items.size(); ++i) {
        _items.at(i)->setZOrder(-std::abs(i - _index) * 100);
        float x = calcFunction(i - _index, menuSize.width / 2);
        auto moveTo = MoveTo::create(ANIMATION_DURATION, Vec2(menuSize.width / 2 + x, menuSize.height / 2));
        _items.at(i)->runAction(moveTo);
        auto scaleTo = ScaleTo::create(ANIMATION_DURATION, 1 - std::abs(calcFunction(i - _index, MENU_SCALE)));
        _items.at(i)->runAction(scaleTo);
        auto orbit1 = OrbitCamera::create(ANIMATION_DURATION, 1, 0, calcFunction(i - _lastIndex, MENU_ASLOPE), calcFunction(i - _index, MENU_ASLOPE) - calcFunction(i - _lastIndex, MENU_ASLOPE), 0, 0);
        _items.at(i)->runAction(orbit1);
    }
    scheduleOnce(schedule_selector(SelectGate::actionEndCallBack), ANIMATION_DURATION);
}

void SelectGate::reset()
{
    _lastIndex = 0;
    _index = 0;
}

void SelectGate::setIndex(int index)
{
    _lastIndex = _index;
    _index = index;
}

float SelectGate::getIndex()
{
    return _index;
}

MenuItem *SelectGate::getCurrentItem()
{
    if (_items.size() == 0) {
        return nullptr;
    }
    return _items.at(_index);
}

bool SelectGate::onTouchBegan(Touch *touch, Event *event)
{
    //先停止所有可能存在的动作
    for (ssize_t i = 0; i < _items.size(); ++i) {
        _items.at(i)->stopAllActions();
    }
    if (_selectedItem) {
        _selectedItem->unselected();
    }
    Vec2 position = convertToNodeSpace(touch->getLocation());
    Size size = getContentSize();
    Rect rect = Rect(0, 0, size.width, size.height);
    if (rect.containsPoint(position)) {
        return true;
    }
    return false;
}

void SelectGate::onTouchMoved(Touch *touch, Event *event)
{
    float xDelta = touch->getDelta().x;
    Size size = getContentSize();
    _lastIndex = _index;
    _index -= xDelta / (size.width * ITEM_SIZE_SCALE);
    updatePosition();
    return;
}

void SelectGate::onTouchEnded(Touch *touch, Event *event)
{
    Size size = getContentSize();
    float xDelta = touch->getLocation().x - touch->getStartLocation().x;
    rectify(xDelta > 0);
    if (std::abs(xDelta) < size.width / 24 && _selectedItem) {
        _selectedItem->activate();
    }
    updatePositionWithAnimation();
    return;
}

void SelectGate::rectify(bool forward)
{
    float index = getIndex();
    if (index < 0) {
        index = 0;
    }
    if (index > _items.size() - 1) {
        index = _items.size() - 1;
    }
    if (forward) {
        index = (int)(index + 0.4);
    }
    else {
        index = (int)(index+ 0.6);
    }
    setIndex((int)index);
}

void SelectGate::actionEndCallBack(float dx)
{
    _selectedItem = getCurrentItem();
    if (_selectedItem) {
        _selectedItem->selected();
    }
}

float SelectGate::calcFunction(float index, float width)
{
    return width * index / (std::abs(index) + CALC_A);
}