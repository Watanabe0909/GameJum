#pragma once

#include "..\DirectXTK.h"
#include "..\Texture.h"

class ObjectBase
{
protected:
	Texture *handle;	//グラフィックハンドル 
	int grp_x;			//元画像のｘ座標 
	int grp_y;			//元画像のｙ座標 
	int grp_w;			//元画像の幅 
	int grp_h;			//元画像の高さ 
	float pos_x;		//座標x 
	float pos_y;		//座標y 
	float spd_x;		//速度x 
	float spd_y;		//速度y 
	int state;			//状態

public:
	void SetHandle(Texture *p);
	Texture* GetHandle();
	void SetGrpX(float x);
	float GetGrpX();
	void SetGrpY(float y);
	float GetGrpY();
	void SetGrpW(float w);
	float GetGrpW();
	void SetGrpH(float h);
	float GetGrpH();
	void SetPosX(float x);
	float GetPosX();
	void SetPosY(float y);
	float GetPosY();
	void SetSpdX(float x);
	void SetSpdY(float y);
	void SetState(int n);
	int GetState();
	void Update();
	void Render();
};