#include "MovedTiled.h"
void MovedTiled::showAt(int r,int c){
	moveTo(r,c);
	auto bk = this -> getChildByTag(110);
	bk->runAction(
                Sequence::create(
                        ScaleTo::create(0.2, 0.8),
                        ScaleTo::create(0.2, 1.2),
                        ScaleTo::create(0.2, 1)
                                   , NULL));
}
void MovedTiled::doubleNumber(){
	this -> m_number = this ->m_number * 2;
	auto bk = this -> getChildByTag(110);
	auto label = (Label *) bk -> getChildByTag(10);
	label ->setString(StringUtils::format("%d",m_number));
	bk->runAction(
                Sequence::create(
                        ScaleTo::create(0.2, 0.8),
                        ScaleTo::create(0.2, 1.2),
                        ScaleTo::create(0.2, 1)
                                   , NULL));
    switch (this->m_number) {
        case 2:
            bk->setColor(Color3B(230,220,210));
             
        case 4:
            bk->setColor(Color3B(230,210,190));
            break;
        case 8:
            bk->setColor(Color3B(230,150,100));
            label->setColor(Color3B(255,255,255));
            break;
        case 16:
            bk->setColor(Color3B(230,120,80));
            label->setColor(Color3B(255,255,255));
            break;
        case 32:
            bk->setColor(Color3B(230,100,90));
            label->setColor(Color3B(255,255,255));
            break;
        case 64:
            bk->setColor(Color3B(230,70,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 128:
            bk->setColor(Color3B(230,190,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 256:
            bk->setColor(Color3B(230,190,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 512:
            bk->setColor(Color3B(230,190,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 1024:
        case 2048:
            label->setScale(0.5);
            bk->setColor(Color3B(210,180,30));
            label->setColor(Color3B(255,255,255));
    }
}
void MovedTiled::moveTo(int r,int c){
	this -> m_row = r;
	this -> m_col = c;
	this -> setPosition(Point(
		c * GAME_TILED_WIDTH + GAME_TILED_BOARD_WIDTH * (c + 1),
		r * GAME_TILED_HEIGHT + GAME_TILED_BOARD_WIDTH * (r + 1)
		));
}
bool MovedTiled::init(){
	if(!Node::init()){
		return false;
	}
	//±³¾°²ã
	auto bk = LayerColor::create(
		Color4B(200,200,200,255),GAME_TILED_WIDTH,GAME_TILED_HEIGHT
		);
	this -> addChild(bk);
	bk->setTag(110);
	//Êý×Ö²ã
	int n = rand() % 10;
	this -> m_number = n > 0 ? 2 : 4;
	switch (this->m_number) {
        case 2:
            bk->setColor(Color3B(230,220,210));
             
        case 4:
            bk->setColor(Color3B(230,210,190));
            break;
	}
	auto label = Label::createWithSystemFont(
			(StringUtils::format("%d",this->m_number)),"ËÎÌå",40
			);
	label->setTag(10);
	//label -> setString(StringUtils::format("%d",this->m_number));
	//label -> setScale(4);
	label -> setColor(
		Color3B::BLACK
		);
	bk -> addChild(label);
	label->setPosition(Point(
		GAME_TILED_WIDTH/2,
		GAME_TILED_HEIGHT/2
		));
	return true;
}