#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOver.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)))
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCDirector* dir = CCDirector::sharedDirector();
    CCSize winsize = dir->getWinSize();
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
    pLabel->setPosition(ccp(winsize.width/2, winsize.height - 30));
    this->addChild(pLabel);
    
    CCSprite* player = CCSprite::create("Player.png");
    player->setPosition(ccp(player->getContentSize().width/2, winsize.height/2));
    this->addChild(player);
    
    this->schedule(schedule_selector(HelloWorld::Update_CreatedEnemy), 1.0f);
    this->scheduleUpdate();
    this->setTouchEnabled(true);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav", true);
    
    return true;
}

HelloWorld::~HelloWorld()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    list_Bullet.clear();
    list_Enemy.clear();
}

void HelloWorld::update(float delta)
{
    for(int i = list_Enemy.size()-1; i >= 0; --i)
    {
        bool isDelete = false;
        CCRect enemy_Rect = list_Enemy[i]->boundingBox();
        
        for(int j = 0; j < list_Bullet.size(); ++j)
        {
            if(enemy_Rect.intersectsRect(list_Bullet[j]->boundingBox()) == true)
            {
                isDelete = true;
                CCNode* deleteNode = list_Bullet[j];
                list_Bullet.erase(list_Bullet.begin() + j);
                this->removeChild(deleteNode, true);
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pew-pew-lei.wav");
                
                GameOverScene* overScene = GameOverScene::create();
                overScene->Set_Lose();
                CCScene* scene = CCTransitionFade::create(2.0f, overScene);
                CCDirector::sharedDirector()->replaceScene(scene);
                break;
            }
        }
        
        if(isDelete == true)
        {
            CCNode* deleteNode = list_Enemy[i];
            list_Enemy.erase(list_Enemy.begin() + i);
            this->removeChild(deleteNode, true);
        }
    }
}

void HelloWorld::Update_CreatedEnemy(float dt)
{
    CreateEnemy();
}
void HelloWorld::Callback_MoveFinish(CCNode* node)
{
    if(node != NULL)
    {
        if(node->getTag() == 1) //enemy
        {
            for(int i=0; i<list_Enemy.size(); ++i)
            {
                if(list_Enemy[i] == node)
                {
                    list_Enemy.erase(list_Enemy.begin() + i);
                    break;
                }
            }
        }
        else if(node->getTag() == 2) //bullet
        {
            for(int i=0; i<list_Bullet.size(); ++i)
            {
                if(list_Bullet[i] == node)
                {
                    list_Bullet.erase(list_Bullet.begin() + i);
                    break;
                }
            }
        }
        this->removeChild(node, true);
    }
}
void HelloWorld::CreateEnemy()
{
    CCSprite* enemy = CCSprite::create("Target.png");
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize enemySize = enemy->getContentSize();
    
    int minY = enemySize.height/2;
    int maxY = winSize.height - minY;
    int rangeY = maxY - minY;
    int posY = minY + (rand() % rangeY);
    enemy->setPosition(ccp(winSize.width - (enemySize.width/2), posY));
    
    int duration = 2 + (rand() % 3);
    CCFiniteTimeAction* move = CCMoveTo::create(duration, ccp(-enemySize.width/2,posY));
    CCFiniteTimeAction* callBack = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::Callback_MoveFinish));
    CCAction* action = CCSequence::create(move, callBack, NULL);
    enemy->runAction(action);
    
    enemy->setTag(1);
    this->addChild(enemy);
    list_Enemy.push_back(enemy);
}

void HelloWorld::CreateBullet(CCPoint touchPos)
{
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* bullet = CCSprite::create("Projectile.png");
    CCPoint pos = ccp(20, winsize.height/2);
    bullet->setPosition(pos);
    
    CCPoint desti = ccpNormalize(ccpSub(touchPos, pos));
    desti.x = (pos.x + (desti.x * 500.0f));
    desti.y = (pos.y + (desti.y * 500.0f));
    CCFiniteTimeAction* move = CCMoveTo::create(3.0f, desti);
    CCFiniteTimeAction* callBack = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::Callback_MoveFinish));
    CCAction* action = CCSequence::create(move, callBack, NULL);
    bullet->runAction(action);
    
    bullet->setTag(2);
    this->addChild(bullet);
    list_Bullet.push_back(bullet);
}

void HelloWorld::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)pTouches->anyObject();
    CreateBullet(touch->getLocation());
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
