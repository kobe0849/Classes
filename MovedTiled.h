#ifndef __MOVEDTILED_H_
#define __MOVEDTILED_H_

#include "cocos2d.h"
#include "const.h"
USING_NS_CC;
class MovedTiled : public Node
{
  public:
    int m_row; //��
    int m_col; //��
    int m_number;//����
    void showAt(int r,int c);//��ĳ��λ����ʾ�����
    void moveTo(int r,int c);//�ƶ���r�� c��
    void doubleNumber();//X2
    CREATE_FUNC(MovedTiled);
    bool init();
};
#endif