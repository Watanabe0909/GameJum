//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Goal.h
//!
//! @brief  ゴール処理のヘッダファイル
//!
//! @date   2017/04/10
//!
//! @author 加藤 竜哉
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//	多重インクルードの防止
#pragma once

//	ヘッダファイルのインクルード
#include "..\ObjectBase.h"

class Goal : public ObjectBase
{
private:
	static const int GOAL_GRP_W = 32;		//	ゴール画像の幅
	static const int GOAL_GRP_H = 32;		//	ゴール画像の高さ
public:
	Goal(int pos_x, int pos_y);				//コンストラクタ
	~Goal();								//デストラクタ
};
