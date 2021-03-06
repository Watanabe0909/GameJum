//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Press.cpp
//!
//! @brief  プレス機処理のソースファイル
//!
//! @date   2017/04/08
//!
//! @author 渡邊真人
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//ヘッダファイルのインクルード
#include "SidePress.h"

//----------------------------------------------------------------------
//! @brief コンストラクタ
//!
//! @param[in] x座標、y座標
//----------------------------------------------------------------------
SidePress::SidePress(int pos_x, int pos_y)
	:m_count(0)			//カウント
{
	m_handle = new Texture(L"Resources\\Images\\SidePress.png");	//画像
	m_pos_x = pos_x;											//x座標
	m_pos_y = pos_y;											//y座標
	m_grp_x = 0;												//元画像のgrp_x
	m_grp_y = 0;												//元画像のgrp_y
	m_grp_w = SIDEPRESS_GRP_W;									//元画像のgrp_w				
	m_grp_h = SIDEPRESS_GRP_H;									//元画像のgrp_h				
}

//----------------------------------------------------------------------
//! @brief デストラクタ
//----------------------------------------------------------------------
SidePress::~SidePress()
{
	delete m_handle;	//画像
}

//----------------------------------------------------------------------
//! @brief 移動
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void SidePress::Move()
{

	m_count++;

	//右移動
	if (m_count < CHANGE_MOVE_COUNT / 2)
		m_spd_x = 1.0f;
	//左移動
	if (m_count > CHANGE_MOVE_COUNT / 2)
		m_spd_x = -1.0f;
	//reset
	if (m_count >= CHANGE_MOVE_COUNT)
		m_count = 0;

}