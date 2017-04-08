//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   2017/04/07		
//!
//! @author 加藤 竜哉
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

// ヘッダファイルの読み込み ================================================
#define _GAMEMAIN_
#include "Player.h"
#include "GameMain.h"
#include "GameBase.h"
#include "GamePlay.h"
#include "GameTitle.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Box.h"
#include <ctime>

using namespace DirectX::SimpleMath;
using namespace DirectX;

// プロトタイプ宣言 ====================================================

// グローバル変数の定義 ====================================================
Texture *g_grpBack;
Texture *g_grpResult;
Texture *g_grpOver;
Texture *g_grpTitle;
GameBase* base;

// 関数の定義 ==============================================================

//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeGame(void)
{

	base = new Title();

	ADX2Le::Initialize("Nightmare.acf");
	ADX2Le::LoadAcb("Resources\\Sounds\\CueSheet_0.acb");

	g_NextScene = g_scene;
}




//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateGame(void)
{
	//音
	ADX2Le::Update();

	//シーン管理
	if (g_NextScene != g_scene)
	{
		g_scene = g_NextScene;
		delete base;
		g_init = 0;


		//シーンごとの呼び出し
		switch (g_scene)
		{
		case TITLE:
			base = new Title();
			break;

		case PLAY:
			base = new Play();
			break;

		case CLEAR:
			base = new Clear();
			break;

		case OVER:
			base = new Over();
			break;
		}
	}

	g_key_old = g_key_code;
	base->Update();
}



//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderGame(void)
{

	base->Render();
	
}



//----------------------------------------------------------------------
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeGame(void)
{
	ADX2Le::Finalize();
	
	delete base;
	delete g_grpBack;
	delete g_grpResult;
	delete g_grpTitle;
}



//----------------------------------------------------------------------
//! @brief テクスチャの描画
//!
//! @param[in] xy座標，画像の始点xy, 画像の大きさwh, テクスチャ
//!
//! @return なし
//----------------------------------------------------------------------
void DrawRectTexture(int pos_x, int pos_y, int tex_x, int tex_y, int tex_w, int tex_h, Texture* handle)
{
	//rect = { leftupX, leftupY, rightdownX, rightdownY };
	RECT rect = { tex_x, tex_y, tex_x + tex_w, tex_y + tex_h };

	//Draw(テクスチャ, 場所 , 大きさ, 色合い, 回転(ラジアン), 回転するときの中心座標 , 拡大倍率)
	g_spriteBatch->Draw(handle->m_pTexture, Vector2((float)pos_x, (float)pos_y), &rect, 
							Colors::White, 0.0f, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
}






