#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>

using namespace std;

class HelloWorld : public cocos2d::CCLayerColor
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
    virtual void update(float delta) override;
    virtual ~HelloWorld();
private:
    void Update_CreatedEnemy(float dt);
    void Callback_MoveFinish(CCNode* enemy);
    void CreateEnemy();
    void CreateBullet(cocos2d::CCPoint touchPos);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) override ;
private:
    vector<CCNode*> list_Enemy;
    vector<CCNode*> list_Bullet;
};

#endif // __HELLOWORLD_SCENE_H__
