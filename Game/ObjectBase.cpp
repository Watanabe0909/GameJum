#include "ObjectBase.h"
#include "GameMain.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

void  ObjectBase::SetHandle(Texture *p)
{
	handle = p;
}

Texture*  ObjectBase::GetHandle()
{
	return handle;
}

void ObjectBase::SetGrpX(float x)
{
	grp_x = x;
}

float  ObjectBase::GetGrpX()
{
	return grp_x;
}

void  ObjectBase::SetGrpY(float y)
{
	grp_y = y;
}

float  ObjectBase::GetGrpY()
{
	return grp_y;
}

void  ObjectBase::SetGrpW(float w)
{
	grp_w = w;
}

float  ObjectBase::GetGrpW()
{
	return grp_w;
}

void  ObjectBase::SetGrpH(float h)
{
	grp_h = h;
}

float ObjectBase::GetGrpH()
{
	return grp_h;
}

void ObjectBase::SetPosX(float x)
{
	pos_x = x;
}

float ObjectBase::GetPosX()
{
	return pos_x;
}

void ObjectBase::SetPosY(float y)
{
	pos_y = y;
}

float ObjectBase::GetPosY()
{
	return pos_y;
}

void ObjectBase::SetSpdX(float x)
{
	spd_x = x;
}

void ObjectBase::SetSpdY(float y)
{
	spd_y = y;
}

void ObjectBase::SetState(int n)
{
	state = n;
}

int ObjectBase::GetState()
{
	return state;
}

void ObjectBase::Update()
{
	pos_x = pos_x + spd_x;
	pos_y = pos_y + spd_y;
}

void ObjectBase::Render()
{
	RECT rect;

	rect = { grp_x, grp_y, grp_x + grp_w, grp_y + grp_h };

	g_spriteBatch->Draw(handle->m_pTexture, Vector2(pos_x, pos_y),
		&rect, Colors::White, 0.0f, Vector2(0, 0), 1.0f);
}