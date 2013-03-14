//
//  Unit_Base.cpp
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#include "Unit_Base.h"

Unit_Base::Unit_Base()
{

}

Unit_Base::~Unit_Base()
{
    
}

bool Unit_Base::init()
{
    sprite = NULL;
    return true;
}

void Unit_Base::SetParent(CCNode* parent)
{
    if(parent != NULL && sprite != NULL)
    {
        parent->addChild(sprite);
    }
}

void Unit_Base::setPosition(const cocos2d::CCPoint &var)
{
    if(sprite != NULL)
    {
        sprite->setPosition(var);
    }
}