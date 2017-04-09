//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Camera.h
//!
//! @brief  カメラ処理のヘッダファイル
//!
//! @date   2017/04/09
//!
//! @author 佐久間尚輝
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

#include "ObjectBase.h"

class Camera	:public ObjectBase
{
public:
	Camera();	//コンストラクタ
	~Camera();	//デストラクタ
	void Coordinate(int pos_x, int grp_w);	//座標変更
	void CameraMaxPos();					//スクロールの限界
};
