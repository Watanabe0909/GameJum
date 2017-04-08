//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SidePress.cpp
//!
//! @brief  横に挟むギミックのヘッダファイル
//!
//! @date   2017/04/08
//!
//! @author 渡邊真人
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//	多重インクルードの防止
#pragma once

//	ヘッダファイルの読み込み
#include "..\ObjectBase.h"
class SidePress : public ObjectBase
{
private:
	static const int SIDEPRESS_GRP_W = 64;	//プレス機の幅
	static const int SIDEPRESS_GRP_H = 64; //プレス機の高さ
	int m_count;						//カウント

public:
	SidePress(int pos_x, int pos_y);	//コンストラクタ
	~SidePress();						//デストラクタ
	void Move();						//移動
};