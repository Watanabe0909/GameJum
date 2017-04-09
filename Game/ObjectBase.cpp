//	ヘッダファイルのインクルード
#include "ObjectBase.h"
#include "GameMain.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

//	ハンドルの設定
void  ObjectBase::SetHandle(Texture *p)
{
	m_handle = p;
}

//	ハンドルの取得
Texture*  ObjectBase::GetHandle()
{
	return m_handle;
}

//	ハンドル座標xの設定
void ObjectBase::SetGrpX(float x)
{
	m_grp_x = x;
}

//	ハンドル座標xの取得
float  ObjectBase::GetGrpX()
{
	return m_grp_x;
}

//	ハンドル座標yの設定
void  ObjectBase::SetGrpY(float y)
{
	m_grp_y = y;
}

//	ハンドル座標yの取得
float  ObjectBase::GetGrpY()
{
	return m_grp_y;
}

//	オブジェクトの幅設定
void  ObjectBase::SetGrpW(float w)
{
	m_grp_w = w;
}

//	オブジェクトの幅を取得
float  ObjectBase::GetGrpW()
{
	return m_grp_w;
}

//	オブジェクトの高さを設定
void  ObjectBase::SetGrpH(float h)
{
	m_grp_h = h;
}

//	オブジェクトの高さを設定
float ObjectBase::GetGrpH()
{
	return m_grp_h;
}

//	オブジェクトの座標xを設定
void ObjectBase::SetPosX(float x)
{
	m_pos_x = x;
}

//	オブジェクトの座標xを取得
float ObjectBase::GetPosX()
{
	return m_pos_x;
}

//	オブジェクトの座標yを設定
void ObjectBase::SetPosY(float y)
{
	m_pos_y = y;
}

//	オブジェクトの座標yを取得
float ObjectBase::GetPosY()
{
	return m_pos_y;
}

//	オブジェクトのスピードyの設定
void ObjectBase::SetSpdX(float x)
{
	m_spd_x = x;
}

//	オブジェクトのスピードyの取得
void ObjectBase::SetSpdY(float y)
{
	m_spd_y = y;
}

//	オブジェクトのステートを設定
void ObjectBase::SetState(int n)
{
	m_state = n;
}

//	オブジェクトのステートを取得
int ObjectBase::GetState()
{
	return m_state;
}

//	オブジェクトの更新処理
void ObjectBase::Update()
{
	m_pos_x = m_pos_x + m_spd_x;
	m_pos_y = m_pos_y + m_spd_y;
}

//	オブジェクトの描画処理
void ObjectBase::Render()
{
	//	画像の短形用変数
	RECT rect;

	rect = { m_grp_x, m_grp_y, m_grp_x + m_grp_w, m_grp_y + m_grp_h };

	g_spriteBatch->Draw(m_handle->m_pTexture, Vector2(m_pos_x, m_pos_y),
		&rect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);
}

//オブジェクトの描画処理(スクロールに対応)
void ObjectBase::Render(int camera_pos_x)
{
	//	画像の短形用変数
	RECT rect;

	rect = { m_grp_x, m_grp_y, m_grp_x + m_grp_w, m_grp_y + m_grp_h };

	g_spriteBatch->Draw(m_handle->m_pTexture, Vector2(m_pos_x - (camera_pos_x - SCREEN_WIDTH / 2),
		m_pos_y),
		&rect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);

}
