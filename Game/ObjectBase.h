//	多重インクルードの防止
#pragma once

//	ヘッダファイルのインクルード
#include "..\DirectXTK.h"
#include "..\Texture.h"

class ObjectBase
{
protected:
	static const int SCREEN_WIDTH = 640;	//画面の幅
	static const int SCREEN_HEIGHT = 480;	//画面の高さ
	static const int CHIPSIZEx5 = 160;		//マップチップ5つ分
	Texture *m_handle;	//グラフィックハンドル 
	int m_grp_x;			//元画像のｘ座標 
	int m_grp_y;			//元画像のｙ座標 
	int m_grp_w;			//元画像の幅 
	int m_grp_h;			//元画像の高さ 
	float m_pos_x;		//座標x 
	float m_pos_y;		//座標y 
	float m_spd_x;		//速度x 
	float m_spd_y;		//速度y 
	int m_state;			//状態

public:
	void SetHandle(Texture *p);		//	ハンドルの設定
	Texture* GetHandle();			//	ハンドルの取得
	void SetGrpX(float x);			//	ハンドル座標xの設定
	float GetGrpX();				//	ハンドル座標xの取得
	void SetGrpY(float y);			//	ハンドル座標yの設定
	float GetGrpY();				//	ハンドル座標yの取得
	void SetGrpW(float w);			//	オブジェクトの幅を設定
	float GetGrpW();				//	オブジェクトの幅を取得
	void SetGrpH(float h);			//	オブジェクトの高さを設定
	float GetGrpH();				//	オブジェクトの高さを取得
	void SetPosX(float x);			//	オブジェクトの座標xの設定
	float GetPosX();				//	オブジェクトの座標xの取得
	void SetPosY(float y);			//	オブジェクトの座標yの設定
	float GetPosY();				//	オブジェクトの座標yの取得
	void SetSpdX(float x);			//	オブジェクトのスピードxの設定
	void SetSpdY(float y);			//	オブジェクトのスピードyの設定
	void SetState(int n);			//	オブジェクトのステートを設定
	int GetState();					//	オブジェクトのステートを取得
	void Update();					//	更新処理
	void Render();					//	描画処理
	void ObjectBase::Render(int camera_pos_x);//オブジェクトの描画処理(スクロールに対応)

};