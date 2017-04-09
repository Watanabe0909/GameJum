//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameClear.cpp
//!
//! @brief  ゲームクリア処理のソースファイル
//!
//! @date   2017/04/07		
//!
//! @author 加藤 竜哉	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "GameClear.h"
using namespace DirectX::SimpleMath;
using namespace DirectX;

//----------------------------------------------------------------------
//! @brief ゲームクリアコンストラクタ
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
Clear::Clear()
{
	//	クリア画像の初期化
	m_clear_image = new Texture(L"Resources\\Images\\clear.png");
	m_clear_image2 = new Texture(L"Resources\\Images\\clear2.png");

	//	フェード用変数の初期化
	m_fade_flag = false;
	m_alfa = 1.0f;

	//	カウントの初期化
	m_count = 0;
}

//----------------------------------------------------------------------
//! @brief ゲームクリアデストラクタ
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
Clear::~Clear()
{
}

//----------------------------------------------------------------------
//! @brief ゲームクリア処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Clear::Update()
{
	if (g_init == 0)
	{
		g_init = 1;
		g_TimeCnt = 0;
	}

	//	Zキーを押したらタイトルシーンへ
	if (g_keyTracker->pressed.Z)
	{
		ADX2Le::Play(CRI_CUESHEET_1_SE);
		m_fade_flag = true;
	}

	//	フェードフラグがtrueなら透明度を上げる
	if (m_fade_flag == true)
	{
		m_alfa -= 0.01f;
	}
	else
	{
		//	カウントを進める
		m_count++;
	}

	//	カウントが40を超えたら0に戻す
	if (m_count > 40)
	{
		m_count = 0;
	}

	//	透明ならシーンを切り替える
	if (m_alfa <= 0.0f)
	{
		g_NextScene = TITLE;
	}
}

//----------------------------------------------------------------------
//! @brief ゲームクリア描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Clear::Render()
{
	if (m_count <= 20)
	{
		//	画像の描画
		g_spriteBatch->Draw(m_clear_image->m_pTexture, Vector2(0, 0), Color(1.0f, 1.0f, 1.0f, m_alfa));
	}
	else
	{
		//	画像の描画
		g_spriteBatch->Draw(m_clear_image2->m_pTexture, Vector2(0, 0), Color(1.0f, 1.0f, 1.0f, m_alfa));
	}
}
