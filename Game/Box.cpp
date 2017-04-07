//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Box.cpp
//!
//! @brief  箱処理のソースファイル
//!
//! @date   2016/11/28
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//ヘッダインクルード========================================
#include"..\Texture.h"
#include "Box.h"
#include "Player.h"
#include "Gamemain.h"

//関数の定義==============================================
//コンストラクタ
Box::Box()
	:m_box_posx(-32)
	,m_box_posy (0)
	,m_box_grpx (BOX_GRPX)
	,m_box_grpy (BOX_GRPY)
	,m_box_width (BOX_WIDTH)
	,m_box_height (BOX_HEIGHT)
	,m_box_state (false)
{
	m_image = new Texture(L"Resources\\Images\\boximage.png");
}

//デストラクタ
Box::~Box()
{
	delete m_image;
}

//箱の更新
void Box::Box_Update(Player* player)
{
	m_box_posy += m_box_spdy;

	if (m_box_posy > 480)
	{
		m_box_state = false;
	}

	CheckHitPlayer(player);
}

//箱の設置
void Box::Box_Set()
{
	m_box_posx = rand() % (BOX_WIDTH * 15 - BOX_WIDTH);
	m_box_posy = 0;
	m_box_spdy = 5;
	m_box_state = true;
	m_box_type = rand() % BOX_TYPE_NUM;
}

//箱の描画
void Box::Box_Draw()
{
	if (m_box_state)
	{
		DrawRectTexture(m_box_posx, m_box_posy,
			m_box_grpx, m_box_grpy, m_box_width, m_box_height, m_image);
	}
}

//箱の状態チェック
bool Box::ChaeckState()
{
	return m_box_state;
}

//箱とプレイヤーの当たった処理
void Box::CheckHitPlayer(Player* player)
{
	if (player->GetPlayerCenterX() > m_box_posx && player->GetPlayerCenterX() < m_box_posx + m_box_width
		&& player->GetPlayerCenterY() > m_box_posy && player->GetPlayerCenterY() < m_box_posy + m_box_height)
	{
		player->Dead();
	}
}