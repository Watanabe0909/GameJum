//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   MoveBlock.cpp
//!
//! @brief  挟むギミックのヘッダファイル
//!
//! @date   2017/04/07		
//!
//! @author 渡邊真人
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//	多重インクルードの防止
#pragma once

//	ヘッダファイルの読み込み
#include "ObjectBase.h"

//クラス
class Moveblock :public ObjectBase
{
private:
	static const int M_BLOCK_SIZE = 32;						//1ブロックのサイズ
	static const int M_BLOCK_GRP_W = M_BLOCK_SIZE * 3;		//grp_wのサイズ
	static const int M_BLOCK_GRP_H = M_BLOCK_SIZE * 3;		//grp_hのサイズ
	static const int M_BLOCK_POS_X = M_BLOCK_SIZE * 10;		//pos_xのサイズ
	static const int M_BLOCK_SPD_Y_DOWN = 6;				//spd_yの下に動く速度の設定
	static const int M_BLOCK_SPD_Y_UP = -6;					//spd_yの上に動く速度の設定
	static const int m_pos_y_min = 0;						//動く座標の最小値
	static const int m_pos_y_max = M_BLOCK_SIZE * 9;		//動く座標の最大値
	Texture* g_gimmickimage;								//挟むギミック用の画像
public:
	Moveblock();											//コンストラクタ
	~Moveblock();											//デストラクタ
	void MoveUpDown();										//上下に動く
	
};
