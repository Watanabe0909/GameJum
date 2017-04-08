//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.cpp
//!
//! @brief  ゲームプレイ処理のソースファイル
//!
//! @date   2017/04/07		
//!
//! @author 加藤 竜哉
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "GamePlay.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;
using namespace std;
//グローバル変数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝－

//関数の定義＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝－
//----------------------------------------------------------------------
//! @brief プレイシーンのコンストラクタ
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
Play::Play()
{
	m_stage = new Stage;	//ステージ
	m_moveblock = new Moveblock;	//上下に動くギミック
	
	m_sidepress[0] = new SidePress(32 * 8, 32 * 8);
	m_sidepress[1] = new SidePress(32 * 11, 32 * 8);
	
	m_sidepress[0]->SetState(0);
	m_sidepress[1]->SetState(1);
}

//----------------------------------------------------------------------
//! @brief プレイシーンのデストラクタ
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
Play::~Play()
{
	delete m_stage;	//ステージ
	m_stage = nullptr;
	delete m_moveblock;	//上下に動くギミック
	m_moveblock = nullptr;
	for (int i = 0; i < 2; i++)
	{
		delete m_sidepress[i];
		m_sidepress[i] = nullptr;
	}
}

//----------------------------------------------------------------------
//! @brief ゲームプレイの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Play::Update()
{

	//シーンの最初に一回だけ行う初期化処理
	if (g_init == 0)
	{
	}	
	//ステージの更新
	m_stage->Update();

	//上下に動くギミックの更新
	m_moveblock->Update();

	for (int i = 0; i < 2; i++)
	{
		m_sidepress[i]->Update();
		m_sidepress[i]->Move();
	}
}

//----------------------------------------------------------------------
//! @brief ゲームプレイ描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Play::Render()
{
	//ステージの描画
	m_stage->DrawStage();

	//上下に動くギミックの描画
	m_moveblock->Render();

	for (int i = 0; i < 2; i++)
	{
		m_sidepress[i]->Render();
	}
}

