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

	//	ポーズ画像
	m_pause_image = new Texture(L"Resources\\Images\\pause.png");

	//	選択用の線の画像
	m_line_image = new Texture(L"Resources\\Images\\Line.png");

	//	ポーズフラグの初期化
	m_pause_flag = false;

	//	ポーズ選択用変数の初期化
	m_pause_select = 0;


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

	//プレイ画面
	if (!m_pause_flag)
	{
		//ステージの更新
		m_stage->Update();

		if (g_keyTracker->pressed.X)
		{
			m_pause_flag = true;
		}
	}

	//	ポーズフラグがtrueなら下の処理を行う
	if (m_pause_flag)
	{
		//	下キーが押されたら選択を1進める
		if (g_keyTracker->pressed.Down)
		{
			//	SEの再生
			ADX2Le::Play(CRI_CUESHEET_1_SE);
			//	選択用変数に1を足す
			m_pause_select++;

			//	選択用変数が選択肢を超えたら上に戻る
			if (m_pause_select > RETURN_TITLE)
			{
				m_pause_select = RETURN;
			}

			//上下に動くギミックの更新
			m_moveblock->Update();

			//	Xキーが押されたらポーズフラグをtrueにする
			if (g_keyTracker->pressed.X)
			{
				m_pause_select = RETURN;
			}
		}

		//	上キーが押されたら選択を1戻す
		if (g_keyTracker->pressed.Up)
		{
			ADX2Le::Play(CRI_CUESHEET_1_SE);
			//	選択用変数から1を引く
			m_pause_select--;

			//	選択用変数が選択肢を超えたら下に戻る
			if (m_pause_select < RETURN)
			{
				m_pause_select = RETURN_TITLE;
			}
		}

		//	Zキーが押されたら選択によって次に進む
		if (g_keyTracker->pressed.Z)
		{
			ADX2Le::Play(CRI_CUESHEET_1_SE);
			//	選択がRETURNの時ならゲームへ戻る
			if (m_pause_select == RETURN)
			{
				m_pause_flag = false;
			}

			//	選択がRETURN_TITLEならタイトルへ戻る
			if (m_pause_select == RETURN_TITLE)
			{
				g_NextScene = TITLE;
			}
		}

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


	//オブジェクトの描画
	m_stage->ObjectDraw();


	//	ポーズフラグがtrueなら下の処理を行う
	if (m_pause_flag)
	{
		//	画像の描画
		g_spriteBatch->Draw(m_pause_image->m_pTexture, Vector2(0, 0));

		//	選択用変数によって線の位置をずらす
		if (m_pause_select == RETURN)
		{
			//	画像の描画
			g_spriteBatch->Draw(m_line_image->m_pTexture, Vector2(105.0f, 260.0f));
		}
		else if(m_pause_select == RETURN_TITLE)
		{
			//	画像の描画
			g_spriteBatch->Draw(m_line_image->m_pTexture, Vector2(105.0f, 340.0f));
		}
	}


}

