//
//  Unit_Base.h
//  Chess
//
//  Created by 정 기호 on 13. 3. 14..
//
//

#ifndef __Chess__Unit_Base__
#define __Chess__Unit_Base__

#include "cocos2d.h"

using namespace cocos2d;

class Unit_Base
{
public:
    Unit_Base();
    virtual ~Unit_Base();
public:
    void SetParent(CCNode* parent);
    virtual void setPosition(const cocos2d::CCPoint &var);
protected:
    CCSprite* sprite;
protected:
    virtual bool init();
};

#endif /* defined(__Chess__Unit_Base__) */
