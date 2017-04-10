//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Water.h
//!
//! @brief  水処理のヘッダファイル
//!
//! @date   2017/04/10
//!
//! @author 加藤 竜哉
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//	多重インクルードの防止
#pragma once

//	ヘッダファイルのインクルード
#include "..\ObjectBase.h"

class Water : public ObjectBase
{
private:
	static const int WATER_GRP_W = 32;		//	水画像の幅
	static const int WATER_GRP_H = 16;		//	水画像の高さ
public:
	Water(int pos_x, int pos_y);			//コンストラクタ
	~Water();								//デストラクタ
};
