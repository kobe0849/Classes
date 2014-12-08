#include "gamescene.h"
#include <iostream>
using namespace std;
Scene *GameScene::createScene(){
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}
bool GameScene::init(){
	if(!Layer::init()){
		return false;
	}
	//初始化游戏标题
	auto labelGame= Label::createWithBMFont("fonts/futura-48.fnt", "2048");
	labelGame->setPosition(Point(labelGame->getContentSize().width / 2 + 10,GAME_SCREEN_HEIGHT - labelGame -> getContentSize().height/2));
	labelGame -> setScale(1);
	this -> addChild(labelGame);
	//初始化游戏网络
	int tiledWidth  = 	GAME_TILED_WIDTH * GAME_COLS + 
			GAME_TILED_BOARD_WIDTH * (GAME_COLS + 1);
	int tiledHeight =  GAME_TILED_HEIGHT *GAME_ROWS +
			GAME_TILED_BOARD_WIDTH * (GAME_ROWS + 1);
	colorBack = LayerColor::create(Color4B(170,170,170,255),
		GAME_TILED_WIDTH * GAME_COLS + 
			GAME_TILED_BOARD_WIDTH * (GAME_COLS + 1),
		GAME_TILED_HEIGHT *GAME_ROWS +
			GAME_TILED_BOARD_WIDTH * (GAME_ROWS + 1)
			);
	colorBack -> setPosition(Point((GAME_SCREEN_WIDTH - tiledWidth)/2,
		(GAME_SCREEN_HEIGHT - tiledHeight)/2));
	//colorBack -> setPosition(Point(80,80));
	this -> addChild(colorBack);


	//初始化逻辑网格和数组
	//初始化网格的每一个块
	for(int row = 0; row < GAME_ROWS; row++){
		for(int col = 0; col < GAME_COLS; col++){
			auto layerTiled = LayerColor::create
				(Color4B(70,70,70,255),
				GAME_TILED_WIDTH,
				GAME_TILED_HEIGHT	
				);
			layerTiled -> setPosition(Point(
					GAME_TILED_WIDTH * col + 
					GAME_TILED_BOARD_WIDTH * (col + 1),
					GAME_TILED_HEIGHT * row + 
					GAME_TILED_BOARD_WIDTH * (row + 1)				
				));
			colorBack -> addChild(layerTiled);
		}
	}
    for(int i=0;i<GAME_ROWS;i++)
    {
     for(int j=0;j<GAME_COLS;j++)
        {
        map[i][j]=0; //空白
        }
    }
	////初始化数字块
	auto tiled = MovedTiled::create();
	int num = rand() % 16;
	colorBack -> addChild(tiled);
	tiled -> moveTo(num / GAME_ROWS,num % GAME_ROWS);
	m_allTiled.pushBack(tiled);
	map[num / GAME_ROWS][num % GAME_COLS] = m_allTiled.getIndex(tiled) + 1;
	//触摸的处理
	auto event = EventListenerTouchOneByOne::create();
	event -> onTouchBegan = [&](Touch * tou,Event * eve){
			m_x = tou -> getLocation().x;
			m_y = tou -> getLocation().y;
			m_startMove = true;
			return true;
		};
	event -> onTouchMoved = [&](Touch * tou,Event * eve){
			int x = tou -> getLocation().x;
			int y = tou -> getLocation().y;
			CCLOG("%d %d %d %d",m_x,m_y,x,y);
			if(m_startMove && (abs(m_x - x) > 10 || abs(m_y - y) > 10)){
				m_startMove = false;
				E_MOVE_DIR dir;
				if(abs(m_x - x) > abs(m_y - y)){
					if(m_x > x) dir = E_MOVE_DIR::LEFT;
					else		dir = E_MOVE_DIR::RIGHT;
				}else{
					if(m_y < y) dir = E_MOVE_DIR::UP;
					else		dir = E_MOVE_DIR::DOWN;
				}
				moveAllTiled(dir);
			}
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event,this);
	return true;
}
void GameScene::moveAllTiled(E_MOVE_DIR dir){
	switch(dir){
	case E_MOVE_DIR::DOWN:
		moveDown();
		break;
	case E_MOVE_DIR::UP:
		moveUp();
		break;
	case E_MOVE_DIR::LEFT:
		moveLeft();
		break;
	case E_MOVE_DIR::RIGHT:
		moveRight();
		break;
	}

	newMovedTiled();
}
void GameScene::newMovedTiled(){
	auto tiled=MovedTiled::create();
    int freeCount=16-m_allTiled.size();
    int num=rand()%freeCount;
    int row=0;
    int col=0;
    int count=0;
    bool find=false;
    for (; row<GAME_ROWS; row++) {
        for(col=0;col<GAME_COLS;col++)
        { if(map[row][col]==0)
          {
            count++;//记录空白的数量
            if(count>=num)
            {
             find=true;
             break;
            }
          
          }
        }
        if (find) {
            break;
        }
    }
  
    colorBack->addChild(tiled);
    tiled->showAt(row, col);
    m_allTiled.pushBack(tiled);
    map[row][col]=m_allTiled.getIndex(tiled)+1;
	CCLOG("%d %d %d",row,col,map[row][col]);
    ///
    if(freeCount==1)//没有空白区域
        {//判定游戏输赢
           
            //跳转场景
           
            return;
        }
}
void GameScene::moveUp(){
    //向上移动所有的块
    for (int col=0; col<GAME_COLS; col++) {
        for(int row=GAME_ROWS-1;row>=0;row--)
        {
         if(map[row][col]>0)
         {
            for(int row1=row;row1<GAME_ROWS-1;row1++)
             {
               if(map[row1+1][col]==0)
                {
                map[row1+1][col]=map[row1][col];
                map[row1][col]=0;
                m_allTiled.at(map[row1+1][col]-1)->moveTo(row1+1, col);
                }
                else
                {//判断，是否可以消除
                   
                int numObj=m_allTiled.at(map[row1+1][col]-1)->m_number;
                int numNow=m_allTiled.at(map[row1][col]-1)->m_number;
                 if(numObj==numNow)
                 {  //m_sound_clear=true;
                   //  m_score+=numObj*2;
                   m_allTiled.at(map[row1+1][col]-1)->doubleNumber();
                   m_allTiled.at(map[row1][col]-1)->removeFromParent();
                   int index=map[row1][col];
                   m_allTiled.erase(map[row1][col]-1);
                   for (int r=0; r<GAME_ROWS; r++)
                    {
                      for (int c=0; c<GAME_COLS; c++) {
                          if(map[r][c]>index)
                             {map[r][c]--;
                          }
                      }
                    }
                   map[row1][col]=0;
                 }
                 break;
                }
             }
         }
       }
    
     
}
     

}
void GameScene::moveDown(){
	for (int col=0; col<GAME_COLS; col++) {
        for(int row = 0;row < GAME_ROWS;row++)
        {
         if(map[row][col]>0)
         {
            for(int row1=row;row1 > 0;row1--)
             {
               if(map[row1-1][col]==0)
                {
                map[row1-1][col]=map[row1][col];
                map[row1][col]=0;
                m_allTiled.at(map[row1-1][col]-1)->moveTo(row1-1, col);
                }
                else
                {//判断，是否可以消除
                   
                int numObj=m_allTiled.at(map[row1-1][col]-1)->m_number;
                int numNow=m_allTiled.at(map[row1][col]-1)->m_number;
                 if(numObj==numNow)
                 {  //m_sound_clear=true;
                   //  m_score+=numObj*2;
                   m_allTiled.at(map[row1-1][col]-1)->doubleNumber();
                   m_allTiled.at(map[row1][col]-1)->removeFromParent();
                   int index=map[row1][col];
                   m_allTiled.erase(map[row1][col]-1);
                   for (int r=0; r<GAME_ROWS; r++)
                    {
                      for (int c=0; c<GAME_COLS; c++) {
                          if(map[r][c]>index)
                             {map[r][c]--;
                          }
                      }
                    }
                   map[row1][col]=0;
                 }
                 break;
                }
             }
         }
       }
	}
}
void GameScene::moveLeft(){
	for (int row=0; row < GAME_ROWS; row++) {
        for(int col = 0;col < GAME_COLS;col++)
        {
			CCLOG("%d %d",row,col);
         if(map[row][col]>0)
         {
			 CCLOG("%d %d\n",row,col);
            for(int col1 = col;col1 > 0;col1--)
             {
				 CCLOG("%d\n",col1);
               if(map[row][col1 - 1]==0)
                {
					CCLOG("%d",map[row][col1]-1);
                map[row][col1 - 1]=map[row][col1];
                map[row][col1]=0;
                m_allTiled.at(map[row][col1-1]-1)->moveTo(row, col1-1);
                }
                else
                {//判断，是否可以消除
                   
                int numObj=m_allTiled.at(map[row][col1-1]-1)->m_number;
                int numNow=m_allTiled.at(map[row][col1]-1)->m_number;
                 if(numObj==numNow)
                 {  //m_sound_clear=true;
                   //  m_score+=numObj*2;
                   m_allTiled.at(map[row][col1-1]-1)->doubleNumber();
                   m_allTiled.at(map[row][col1]-1)->removeFromParent();
                   int index=map[row][col1];
                   m_allTiled.erase(map[row][col1]-1);
                   for (int r=0; r<GAME_ROWS; r++)
                    {
                      for (int c=0; c<GAME_COLS; c++) {
                          if(map[r][c]>index)
                             {map[r][c]--;
                          }
                      }
                    }
                   map[row][col1]=0;
                 }
                 break;
                }
             }
         }
       }
	}
}
void GameScene::moveRight(){
	for (int row=0; row < GAME_ROWS; row++) {
        for(int col = GAME_COLS-1;col >= 0;col--)
        {
			CCLOG("%d %d",row,col);
         if(map[row][col]>0)
         {
			 CCLOG("%d %d\n",row,col);
			 for(int col1 = col;col1 < GAME_COLS - 1;col1++)
             {
				 CCLOG("%d\n",col1);
               if(map[row][col1 + 1]==0)
                {
					CCLOG("%d",map[row][col1]-1);
                map[row][col1 + 1]=map[row][col1];
                map[row][col1]=0;
                m_allTiled.at(map[row][col1 + 1]-1)->moveTo(row, col1 + 1);
                }
                else
                {//判断，是否可以消除
                   
                int numObj=m_allTiled.at(map[row][col1 + 1]-1)->m_number;
                int numNow=m_allTiled.at(map[row][col1]-1)->m_number;
                 if(numObj==numNow)
                 {  //m_sound_clear=true;
                   //  m_score+=numObj*2;
                   m_allTiled.at(map[row][col1 + 1]-1)->doubleNumber();
                   m_allTiled.at(map[row][col1]-1)->removeFromParent();
                   int index=map[row][col1];
                   m_allTiled.erase(map[row][col1]-1);
                   for (int r=0; r<GAME_ROWS; r++)
                    {
                      for (int c=0; c<GAME_COLS; c++) {
                          if(map[r][c]>index)
                             {map[r][c]--;
                          }
                      }
                    }
                   map[row][col1]=0;
                 }
                 break;
                }
             }
         }
       }
	}
}