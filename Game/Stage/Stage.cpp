//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Stage.cpp
//!
//! @brief  ステージ処理のソースファイル
//!
//! @date   2017/04/07
//!
//! @author 佐久間尚輝
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#include "Stage.h"
#include <fstream>
#include <sstream>
#include <SimpleMath.h>

using namespace std;
using namespace DirectX::SimpleMath;
using namespace DirectX;

//----------------------------------------------------------------------
//! @brief コンストラクタ
//!
//! @param[in] なし
//----------------------------------------------------------------------
Stage::Stage()
	:m_press_count(0)	//プレス機のカウント
	,m_burner_count(0)	//バーナーのカウント
{
	m_map_image = new Texture(L"Resources\\Images\\MapChip.png");		//マップの画像
	ImportData("Resources\\map\\map.csv");	//マップの読み込み
	//オブジェクト用
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (m_map[i][j])
			{
				//プレス機の生成
			case PRESS:
				m_press[m_press_count] = new Press(j * CHIPSIZE, i* CHIPSIZE);
				m_press_count++;
				break;
				//バーナーの生成
			case BURNER:
				m_burner[m_burner_count] = new Burner(j * CHIPSIZE, i * CHIPSIZE);
				m_burner_count++;
				break;
			default:
				break;
			}
		}
	}
}

//----------------------------------------------------------------------
//! @brief デストラクタ
//----------------------------------------------------------------------
Stage::~Stage()
{
	delete m_map_image;		//画像
	m_map_image = nullptr;
	for (int i = 0; i < m_press_count; i++)
	{
		delete m_press[i];	//プレス機
		m_press[i] = nullptr;
	}
	for (int i = 0; i < m_burner_count; i++)
	{
		delete m_burner[i];	//バーナー
		m_burner[i] = nullptr;
	}
}

//----------------------------------------------------------------------
//! @brief ステージの描画
//!
//! @param[in] ファイルの名前
//!
//! @return なし
//----------------------------------------------------------------------
void Stage::DrawStage()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			//壁の描画
			switch (m_map[i][j])
			{
			case BACKGROUND :
				DrawSprite(0, 0, CHIPSIZE, CHIPSIZE, i, j);
				break;
				//壁
			case WALL:
				DrawSprite(CHIPSIZE, 0 , CHIPSIZE * WALL, CHIPSIZE, i, j);
				break;
				//横長の壁
			case HORIZONTALWALL:
				DrawSprite(CHIPSIZE * WALL, 0 ,
					CHIPSIZE * HORIZONTALWALL, CHIPSIZE, i, j);
				break;
				//縦長の壁
			case VERTICALWALL:
				DrawSprite(CHIPSIZE * HORIZONTALWALL, 0,
					CHIPSIZE * VERTICALWALL , CHIPSIZE , i, j);
				break;
				//水
			case WATER:
				break;
				//プレス機
			case PRESS:
				DrawSprite(0, 0, CHIPSIZE, CHIPSIZE, i, j);
				break;
				//バーナー
			case BURNER:
				DrawSprite(0, 0, CHIPSIZE, CHIPSIZE, i, j);
				break;
			default:
				break;
			}

		}
	}

}

//----------------------------------------------------------------------
//! @brief アップデート
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Stage::Update()
{
	//プレス機
	for (int i = 0; i < m_press_count; i++)
	{
		m_press[i]->Update();	//座標変更
		m_press[i]->Move();		//移動
	}
	//バーナー
	for (int i = 0; i < m_burner_count; i++)
	{
		m_burner[i]->Ignition();
	}
}

//----------------------------------------------------------------------
//! @brief オブジェクトの描画
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Stage::ObjectDraw()
{
	//プレス機
	for (int i = 0; i < m_press_count; i++)
		m_press[i]->Render();
	//バーナー
	for (int i = 0; i < m_burner_count; i++)
	{
		//バーナーが生きている時
		if (m_burner[i]->GetState() == true)
			m_burner[i]->Render();
	}

}


//----------------------------------------------------------------------
//! @brief csvファイルの読み込み
//!
//! @param[in] ファイルの名前
//!
//! @return なし
//----------------------------------------------------------------------
void Stage::ImportData(string filename)
{
	ifstream ifs(filename);
	string str;
	int i;
	if (!ifs)
	{
		for (i = 0; i < MAX_TIP; i++)
		{
			m_map[i / MAP_WIDTH][i % MAP_WIDTH] = 0;
		}
	}

	i = 0;
	while (getline(ifs, str))
	{
		string token;
		istringstream stream(str);

		//一行のうち、文字列とコンマを分割する
		while (getline(stream, token, ','))
		{
			//すべて文字列として読み込まれるため
			//数値は変換が必要
			m_map[i / MAP_WIDTH][i % MAP_WIDTH] = atoi(token.c_str());
			i++;
		}
	}

}

//----------------------------------------------------------------------
//! @brief スプライトの描画
//!
//! @param[in] 画像のAABB、高さ、幅
//!
//! @return なし
//----------------------------------------------------------------------
void Stage::DrawSprite(int grp_x, int grp_y, int grp_w, int grp_h, int i,int j)
{
	RECT rect = { grp_x,grp_y,grp_w,grp_h };
	g_spriteBatch->Draw(m_map_image->m_pTexture, Vector2(CHIPSIZE * j, CHIPSIZE * i),
		&rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

}