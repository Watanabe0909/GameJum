#include "Burner.h"
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Burner.cpp
//!
//! @brief  バーナーの処理のソースファイル
//!
//! @date   2017/04/08
//!
//! @author 佐久間尚輝
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//----------------------------------------------------------------------
//! @brief コンストラクタ
//!
//! @param[in] なし
//----------------------------------------------------------------------
Burner::Burner(int pos_x, int pos_y)
	:m_count(0)
{
	m_handle = new Texture(L"Resources\\Images\\Burner.png");	//画像
	m_pos_x = pos_x;			//x座標
	m_pos_y = pos_y;			//y座標
	m_grp_x = 0;				//元画像のgrp_x
	m_grp_y = 0;				//元画像のgrp_y
	m_grp_w = BURNER_GRP_W;		//元画像のgrp_w
	m_grp_h = BURNER_GRP_H;		//元画像のgrp_h
	m_state = false;
}

//----------------------------------------------------------------------
//! @brief デストラクタ
//----------------------------------------------------------------------
Burner::~Burner()
{
	delete m_handle;
	m_handle = nullptr;
}

//----------------------------------------------------------------------
//! @brief 火をつける
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Burner::Ignition()
{
	m_count++;
	//消す
	if (m_count < STETA_COUNT / 2)
		m_state = false;
	//つける
	if (m_count > STETA_COUNT / 2)
		m_state = true;
	//reset
	if (m_count > STETA_COUNT)
		m_count = 0;

}
