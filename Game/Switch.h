//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Switch.cpp
//!
//! @brief  スイッチのヘッダファイル
//!
//! @date   2017/04/09	
//!
//! @author 渡邊真人
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//	多重インクルードの防止
#pragma once

//	ヘッダファイルの読み込み
#include "ObjectBase.h"

//クラス
class Switch :public ObjectBase
{
private:
	static const int M_SWTICH_GRP = 32;
	static const int M_ONSWTICH_GRP = 64;
public:
	Switch(int pos_x, int pos_y);
	~Switch();
	void Swtiching();
};