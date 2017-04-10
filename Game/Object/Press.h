//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Press.h
//!
//! @brief  プレス機処理のヘッダファイル
//!
//! @date   2017/04/08
//!
//! @author 佐久間尚輝
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

#include "..\ObjectBase.h"
class Press : public ObjectBase
{
private:
	static const int PRESS_GRP_W = 64;	//プレス機の幅
	static const int PRESS_GRP_H = 288; //プレス機の高さ
	static const int MOVE_COUNT = 120;	//移動カウント
	int m_count;	//カウント
public:
	Press(int pos_x, int pos_y);	//コンストラクタ
	~Press();		//デストラクタ
	void Move();	//移動
	void Stop();	//停止
};