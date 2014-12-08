#ifndef __SPALSH_H_
#define __SPLASH_H_

#include "cocos2d.h"
#include "const.h"
#include "GameScene.h"
USING_NS_CC;
class Splash : public Layer
{
    bool init();
 public:
    CREATE_FUNC(Splash);
    static Scene * createScene();
    void jumpToGame(float t);
};
#endif