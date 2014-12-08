#include "Splash.h"
bool Splash::init(){
    if(!Layer::init())
    {
    return false;
    }
    //显示游戏名称
    auto labelGame= Label::createWithBMFont("fonts/futura-48.fnt", "2048");
    labelGame->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
    this->addChild(labelGame);
    labelGame->setScale(1.5);
    //显示制作单位
    auto labelGameVec=Label::createWithBMFont("fonts/futura-48.fnt", "VINO 2014.12.4");
    labelGameVec->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/4));
    this->addChild(labelGameVec);
    labelGameVec->setScale(0.8);
    //计划任务3秒钟之后，自动跳转到游戏场景
    this->scheduleOnce(schedule_selector(Splash::jumpToGame), 3);
    return true;
}
Scene * Splash::createScene(){
	auto scene = Scene::create();
	auto layer = Splash::create();
	scene ->addChild(layer);
	return scene;
}
void Splash::jumpToGame(float t){
	auto scene = GameScene::createScene();
	Director::getInstance() ->replaceScene(
		TransitionProgressOutIn::create(0.5,scene)
		);
}