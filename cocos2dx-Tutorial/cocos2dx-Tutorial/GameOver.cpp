//
//  GameOver.cpp
//  cocos2dx-Tutorial
//
//  Created by 정 기호 on 13. 3. 13..
//
//

#include "GameOver.h"

using namespace cocos2d;

bool GameOverScene::init()
{
    CCScene::init();
    
    layer = GameOverLayer::create();
    this->addChild(layer);
    
    return true;
}

void GameOverScene::Set_Win()
{
    layer->Set_Label("You Win!!!");
}

void GameOverScene::Set_Lose()
{
    layer->Set_Label("You Lose!!");
}

//================================================================================================

bool GameOverLayer::init()
{
    CCLayerColor::initWithColor(cocos2d::ccc4(255, 255, 255, 255));
        
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* sprite = CCSprite::create("HelloWorld.png");
    sprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(sprite);
    
    return true;
}

void GameOverLayer::Set_Label(const char* str)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF* label = CCLabelTTF::create(str, "Thonburi", 34);
    label->setPosition(ccp(size.width/2, size.height - 40));
    this->addChild(label);
}