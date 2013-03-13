//
//  GameOver.h
//  cocos2dx-Tutorial
//
//  Created by 정 기호 on 13. 3. 13..
//
//

#ifndef __cocos2dx_Tutorial__GameOver__
#define __cocos2dx_Tutorial__GameOver__

#include "cocos2d.h"


class GameOverLayer : public cocos2d::CCLayerColor
{
public:
    CREATE_FUNC(GameOverLayer);
    virtual bool init();
public:
    void Set_Label(const char* str);
};

class GameOverScene : public cocos2d::CCScene
{
public:
    CREATE_FUNC(GameOverScene);
    virtual bool init();
public:
    void Set_Win();
    void Set_Lose();
private:
    GameOverLayer* layer;
};


#endif /* defined(__cocos2dx_Tutorial__GameOver__) */
