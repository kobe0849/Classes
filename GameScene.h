#ifndef __GAMESCENE_H_
#define __GAMESCENE_H_
#include "MovedTiled.h"
#include "cocos2d.h"
#include "const.h"
USING_NS_CC;
class GameScene:Layer{
private:
	bool m_startMove;
	int m_x,m_y;
public:
	LayerColor *colorBack;
	E_MOVE_DIR m_dir;
	int map[GAME_ROWS][GAME_COLS];
	Vector< MovedTiled* >m_allTiled;//±£´æËùÓÐ¿é
	static Scene * createScene();
	void moveAllTiled(E_MOVE_DIR dir);
	void newMovedTiled();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	CREATE_FUNC(GameScene);
	bool init();
};
#endif