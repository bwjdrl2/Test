//
//  GameScene_Match.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 13..
//
//

#include "GameScene_Match.h"
#include "Unit_Bishop.h"

bool GameScene_Match::init()
{
    CCScene::init();
    
    CCLayer* layer = GameLayer_Match::create();
    this->addChild(layer);
    
    return true;
}

GameLayer_Match::GameLayer_Match()
{
    
}
GameLayer_Match::~GameLayer_Match()
{
    if(testUnit != NULL)delete testUnit;
}

bool GameLayer_Match::init()
{
    CCLayer::init();
    testUnit = NULL;
    this->setTouchEnabled(true);

    for(int i=0; i<8; ++i)
    {
        for(int j=0; j<8; ++j)
        {
            CCSprite* sprite = NULL;
            if((i+j) % 2 != 0) sprite = CCSprite::create("white.png");
            else sprite = CCSprite::create("black.png");
            
            sprite->setPosition(ccp(30 + 60*j, 20 + 40*i));
            this->addChild(sprite);
        }
    }
    
    testUnit = new Unit_Bishop();
    testUnit->SetParent(this);
    this->scheduleUpdate();
    
    return true;
}
void GameLayer_Match::update(float delta)
{
    //CCDirector::sharedDirector()->replaceScene(GameScene_Match::create());
}