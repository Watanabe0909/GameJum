//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Burner.h
//!
//! @brief  バーナーの処理のヘッダファイル
//!
//! @date   2017/04/08
//!
//! @author 佐久間尚輝
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

#include "..\ObjectBase.h"

class Burner : public ObjectBase
{
private:
	static const int BURNER_GRP_W = 64;
	static const int BURNER_GRP_H = 288;
	static const int STETA_COUNT = 120;
	int m_count; //カウント
public:
	Burner(int pos_x, int pos_y);	//コンストラクタ
	~Burner();			//デストラクタ
	void Ignition();	//火をつける
};
