#ifndef __MOVEDTILED_H_
#define __MOVEDTILED_H_

#include "cocos2d.h"
#include "const.h"
USING_NS_CC;
class MovedTiled : public Node
{
  public:
    int m_row; //行
    int m_col; //列
    int m_number;//数字
    void showAt(int r,int c);//在某个位置显示这个块
    void moveTo(int r,int c);//移动到r行 c列
    void doubleNumber();//X2
    CREATE_FUNC(MovedTiled);
    bool init();
};
#endif