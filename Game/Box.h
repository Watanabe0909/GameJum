//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Box.h
//!
//! @brief  箱処理のヘッダファイル
//!
//! @date   2016/11/28
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

class Texture;
class Player;

//定数の定義================================================
const int BOX_GRPX = (0);
const int BOX_GRPY = (0);
const int BOX_WIDTH = (32);
const int BOX_HEIGHT = (32);
const int BOX_TYPE_NUM = 2;

enum BOX_TYPE
{
	BOX,
	CARROT,
};

//クラスの定義==============================================
class Box
{
private:
	Texture* m_image;
	int m_box_posx, m_box_posy;
	int m_box_width, m_box_height;
	int m_box_grpx, m_box_grpy;
	int m_box_spdy;
	bool m_box_state;
	int m_box_type;
	
public:
	Box();
	~Box();
	void Box_Update(Player* player);
	void Box_Set();
	void Box_Draw();
	bool ChaeckState();
	void CheckHitPlayer(Player*);
};