//--------------------------------------------------------------------------------------
// File: DirectXTK.cpp
//
// DirectXTKに関する関数群
//
// Date: 2015.8.27
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------

#include "DirectXTK.h"
#include "Direct3D.h"

using namespace DirectX;

//////////////////////////////////
// リンクするライブラリ指定		//
//////////////////////////////////
#pragma comment(lib, "DirectXTK.lib")

//////////////////////
// 静的変数			//
//////////////////////
static std::unique_ptr<Keyboard> s_keyboard(new Keyboard);
static std::unique_ptr<Mouse> s_mouse(new Mouse);
std::unique_ptr<CommonStates> g_pCommonStates;


//////////////////////
// グローバル変数	//
//////////////////////

// キーボード関係
Keyboard::State g_key;
std::unique_ptr<Keyboard::KeyboardStateTracker> g_keyTracker(new Keyboard::KeyboardStateTracker);

// マウス関係
Mouse::State g_mouse;
std::unique_ptr<Mouse::ButtonStateTracker> g_mouseTracker(new Mouse::ButtonStateTracker);

// スプライトバッチ
std::unique_ptr<SpriteBatch> g_spriteBatch;

// スプライトフォント
std::unique_ptr<SpriteFont> g_spriteFont;

//--------------------------------------------------------------------------------------
// 初期化
//--------------------------------------------------------------------------------------
void DirectXTK_Initialize()
{
	// スプライトバッチ
	g_spriteBatch.reset(new SpriteBatch(g_pImmediateContext.Get()));

	// スプライトフォント
	g_spriteFont.reset(new SpriteFont(g_pd3dDevice.Get(), L"myfile.spritefont"));

	g_pCommonStates.reset(new CommonStates(g_pd3dDevice.Get()));
}

//--------------------------------------------------------------------------------------
// キー入力やマウス情報の更新
//--------------------------------------------------------------------------------------
void DirectXTK_UpdateInputState()
{
	// キー入力情報を取得
	g_key = s_keyboard->GetState();
	g_keyTracker->Update(g_key);

	// マウス情報を取得
	g_mouse = s_mouse->GetState();
	g_mouseTracker->Update(g_mouse);
}
