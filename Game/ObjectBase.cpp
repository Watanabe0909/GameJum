//	ヘッダファイルのインクルード
#include "ObjectBase.h"
#include "GameMain.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

//	ハンドルの設定
void  ObjectBase::SetHandle(Texture *p)
{
	handle = p;
}

//	ハンドルの取得
Texture*  ObjectBase::GetHandle()
{
	return handle;
}

//	ハンドル座標xの設定
void ObjectBase::SetGrpX(float x)
{
	grp_x = x;
}

//	ハンドル座標xの取得
float  ObjectBase::GetGrpX()
{
	return grp_x;
}

//	ハンドル座標yの設定
void  ObjectBase::SetGrpY(float y)
{
	grp_y = y;
}

//	ハンドル座標yの取得
float  ObjectBase::GetGrpY()
{
	return grp_y;
}

//	オブジェクトの幅設定
void  ObjectBase::SetGrpW(float w)
{
	grp_w = w;
}

//	オブジェクトの幅を取得
float  ObjectBase::GetGrpW()
{
	return grp_w;
}

//	オブジェクトの高さを設定
void  ObjectBase::SetGrpH(float h)
{
	grp_h = h;
}

//	オブジェクトの高さを設定
float ObjectBase::GetGrpH()
{
	return grp_h;
}

//	オブジェクトの座標xを設定
void ObjectBase::SetPosX(float x)
{
	pos_x = x;
}

//	オブジェクトの座標xを取得
float ObjectBase::GetPosX()
{
	return pos_x;
}

//	オブジェクトの座標yを設定
void ObjectBase::SetPosY(float y)
{
	pos_y = y;
}

//	オブジェクトの座標yを取得
float ObjectBase::GetPosY()
{
	return pos_y;
}

//	オブジェクトのスピードyの設定
void ObjectBase::SetSpdX(float x)
{
	spd_x = x;
}

//	オブジェクトのスピードyの取得
void ObjectBase::SetSpdY(float y)
{
	spd_y = y;
}

//	オブジェクトのステートを設定
void ObjectBase::SetState(int n)
{
	state = n;
}

//	オブジェクトのステートを取得
int ObjectBase::GetState()
{
	return state;
}

//	オブジェクトの更新処理
void ObjectBase::Update()
{
	pos_x = pos_x + spd_x;
	pos_y = pos_y + spd_y;
}

//	オブジェクトの描画処理
void ObjectBase::Render()
{
	//	画像の短形用変数
	RECT rect;

	rect = { grp_x, grp_y, grp_x + grp_w, grp_y + grp_h };

	g_spriteBatch->Draw(handle->m_pTexture, Vector2(pos_x, pos_y),
		&rect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);
}