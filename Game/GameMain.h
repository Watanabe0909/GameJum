//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  ゲーム関連のヘッダファイル
//!
//! @date   2017/04/08		
//!
//! @author 加藤 竜哉
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once

#ifndef _GAMEMAIN_
#define EXTERN extern
#else
#define EXTERN
#endif

//	ヘッダファイルのインクルード
#include<windows.h>
#include<d3d11.h>
#include<SimpleMath.h>
#include"..\DirectXTK.h"
#include"..\Texture.h"
#include"..\ADX2Le.h"
#include"CueSheet_0.h"


// 定数の定義 ==============================================================

// ゲームタイトル
#define GAME_TITLE "NightMare"

// ゲーム画面
//#define SCREEN_WIDTH  640    // 幅[pixel]
//#define SCREEN_HEIGHT 480    // 高さ[pixel]


//　列挙型宣言
enum SCENE
{
	LOGO,
	TITLE,
	PLAY,
	CLEAR,
	OVER
};

// グローバル変数の定義 ====================================================


EXTERN int g_key_code;			//キー情報
EXTERN int g_key_old;			//前フレームのキー情報

EXTERN int g_scene;				//シーン管理
EXTERN int g_NextScene;			//次のシーン
EXTERN int g_init;				//初期化管理

EXTERN int g_TimeCnt;			//時間カウンタ
EXTERN int g_Time;				//秒数

EXTERN int g_back_grpx;

EXTERN wchar_t buf[256];


// 関数の宣言 ==============================================================

// ゲームの初期化処理
void InitializeGame(void);

// ゲームの更新処理
void UpdateGame(void);

// ゲームの描画処理
void RenderGame(void);

// ゲームの終了処理
void FinalizeGame(void);

//　数値描画処理
void DrawNum(int x, int y, int n);


//テクスチャの描画
void DrawRectTexture(int pos_x, int pos_y, int tex_x, int tex_y, int tex_w, int tex_h, Texture* handle);

//ランダムゲット
int GetRand(int num);



