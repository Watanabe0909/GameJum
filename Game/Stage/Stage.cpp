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
#include "..\GameMain.h"
#include <fstream>
#include <sstream>
#include <SimpleMath.h>

using namespace std;
using namespace DirectX::SimpleMath;
using namespace DirectX;

//定数
const float Stage::HALF_UP = 0.5f;

//----------------------------------------------------------------------
//! @brief コンストラクタ
//!
//! @param[in] なし
//----------------------------------------------------------------------
Stage::Stage()
	:m_press_count(0)	//プレス機のカウント
	,m_burner_count(0)	//バーナーのカウント
	,m_side_press_count(0)//横のプレス機のカウント
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
				m_press[m_press_count] = new Press(j * CHIPSIZE, i* CHIPSIZE - CHIPSIZE / 2);
				m_press_count++;
				break;
				//横のプレス機の生成
			case SIDEPRESS:
				m_side_press[m_side_press_count] = new SidePress(j * CHIPSIZE + CHIPSIZE / 2, i* CHIPSIZE);
				m_side_press_count++;
				break;
				//バーナーの生成
			case BURNER:
				m_burner[m_burner_count] = new Burner(j * CHIPSIZE, i * CHIPSIZE - CHIPSIZE / 2);
				m_burner_count++;
				break;
				//プレイヤーの生成
			case PLAYER:
				m_player = new Player(j * CHIPSIZE, i * CHIPSIZE);
				break;

				//水の生成
			case WATER:
				m_water[m_water_count] = new Water(j * CHIPSIZE, i * CHIPSIZE + CHIPSIZE / 2);
				m_water_count++;
				break;
				//ゴールの生成
			case GOAL:
				m_goal = new Goal(j * CHIPSIZE, i * CHIPSIZE);

				//スイッチの生成
			case SWITCH:
				m_switch = new Switch(j * CHIPSIZE, i * CHIPSIZE);
				break;
				//スイッチの生成
			case WIND:
				m_wind[m_wind_count] = new Wind(j * CHIPSIZE, i * CHIPSIZE);
				m_wind_count++;
				break;
			default:
				break;
			}
		}
	}
	//カメラ
	m_camera = new Camera();
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
	for (int i = 0; i < m_side_press_count; i++)
	{
		delete m_side_press[i];	//横のプレス機
		m_side_press[i] = nullptr;
	}
	for (int i = 0; i < m_burner_count; i++)
	{
		delete m_burner[i];	//バーナー
		m_burner[i] = nullptr;
	}
	for (int i = 0; i < m_water_count; i++)
	{
		delete m_water[i];	//水
		m_water[i] = nullptr;
	}
	delete m_goal;		//ゴール
	m_goal = nullptr;
	delete m_player;	//プレイヤー
	m_player = nullptr;
	delete m_camera;	//カメラ
	m_camera = nullptr;
	delete m_switch;	//スイッチ
	m_switch = nullptr;
	for (int i = 0; i < m_wind_count; i++)
	{
		delete m_wind[i];		//風
		m_wind[i] = nullptr;
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
				DrawSprite(0, 0, CHIPSIZE, CHIPSIZE, i, j);
				break;
				//ゴール
			case GOAL:
				DrawSprite(0, 0, CHIPSIZE, CHIPSIZE, i, j);
				break;
				//プレス機
			case PRESS:
				DrawSprite(0, 0, CHIPSIZE, CHIPSIZE, i, j);
				break;
				//横のプレス機
			case SIDEPRESS:
				DrawSprite(0, 0, CHIPSIZE, CHIPSIZE, i, j);
				break;
				//バーナー
			case BURNER:
				DrawSprite(0, 0, CHIPSIZE, CHIPSIZE, i, j);
				break;
				//プレイヤー
			case PLAYER:
				DrawSprite(0, 0, CHIPSIZE, CHIPSIZE, i, j);
				break;
				//スイッチ
			case SWITCH:
				DrawSprite(0, 0, CHIPSIZE, CHIPSIZE, i, j);
				break;
				//風
			case WIND:
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
		if (i == 1)									//動かしたいプレス機の要素番号
		{
			if (m_switch->GetState() == false)		//スイッチがオフだったら
			{
				m_press[i]->Stop();		//停止
			}
			else
			{
				m_press[i]->Move();		//移動
			}
		}
		else
		{
			m_press[i]->Move();		//移動
		}
	}

	//バーナー
	for (int i = 0; i < m_burner_count; i++)
	{
		m_burner[i]->Ignition();	//火をつける
	}
	//横のプレス機
	for (int i = 0; i < m_side_press_count; i++)
	{
		m_side_press[i]->Update();	//座標変更
		m_side_press[i]->Move();	//移動
	}
	//カメラ
	m_camera->Coordinate(m_player->GetPosX(),  m_player->GetGrpW());	//座標変更
	m_camera->CameraMaxPos();	//スクロールの限界
	//プレイヤー
	m_player->Move();	//移動
	m_player->Update(); //座標変更
	MapDownDecison();	//マップチップとの下の当たり判定
	MapSideDecison();	//マップチップとの横の当たり判定
	MapJumpDecison();	//マップチップとの上の当たり判定

	//	ジャンプしているなら
	//if (!m_player->GetJump())
	//{
	//	//	プレスとプレイヤーが当たっていたらプレイヤーの大きさを変える
	//	if (CollisionPress())
	//	{
	//		m_player->ChangePlayer();
	//	}
	//}
	//スイッチ
	if (CollisionSwitch())
		m_switch->Swtiching();	//スイッチのオンオフの切り替え

	CollisionWind();	//風とプレイヤーの当たり判定

	//	バーナーと当たっていたらゲームオーバー
	for (int i = 0; i < m_burner_count; i++)
	{
		if (m_burner[i]->GetState() == 1)
		{
			if (CollisionBurner(i))
			{
				g_NextScene = OVER;
			}
		}
	}

	//	水と当たっていたらゲームオーバー
	for (int i = 0; i < m_water_count; i++)
	{
		if (CollisionWater(i))
		{
			//g_NextScene = OVER;
		}
	}

	//	ゴールと当たっていたらゲームクリア
	if (CollisionGoal())
	{
		g_NextScene = CLEAR;
	}

	//プレス機とプレイヤーの当たり判定
	CollisionPress();
	//横のプレス機
	CollisionSidePress();
	m_press_flag = false;	//プレスされていない

	//プレイヤーがマップから落ちた時の判定
	DownMapPlayer();
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
		m_press[i]->Render(m_camera->GetPosX());
	//横のプレス機
	for (int i = 0; i < m_side_press_count; i++)
		m_side_press[i]->Render(m_camera->GetPosX());

	//バーナー
	for (int i = 0; i < m_burner_count; i++)
	{
		//バーナーが生きている時
		if (m_burner[i]->GetState() == true)
			m_burner[i]->Render(m_camera->GetPosX());
	}

	//水
	for (int i = 0; i < m_water_count; i++)
		m_water[i]->Render(m_camera->GetPosX());

	//プレイヤー
	m_player->Render(m_camera->GetPosX());

	//ゴール
	m_goal->Render(m_camera->GetPosX());

	//スイッチ
	m_switch->Render(m_camera->GetPosX());
	//風
	for (int i = 0; i < m_wind_count; i++)
	{
		m_wind[i]->Render(m_camera->GetPosX());
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
	//スクロールに対応
	g_spriteBatch->Draw(m_map_image->m_pTexture, Vector2(CHIPSIZE * j - (m_camera->GetPosX() - SCREEN_WIDTH / 2), CHIPSIZE * i),
		&rect, Colors::White, 0.0f, Vector2(0, 0), Vector2(1, 1));

}

//----------------------------------------------------------------------
//! @brief マップチップとの下の当たり判定
//!
//! @param[in] 
//!
//! @return なし
//----------------------------------------------------------------------

void Stage::MapDownDecison()
{
	int map_x;
	int map_y;
	//左下
	map_x = floor((m_player->GetPosX() + SHIFTED_POS) / CHIPSIZE);
	map_y = floor((m_player->GetPosY() + m_player->GetGrpH()) / CHIPSIZE);
	if ((map_x >= 0 && map_x < MAP_WIDTH) && (map_y >= 0 && map_y < MAP_HEIGHT))
	{
		//マップチップが壁またはスイッチの時
		if (m_map[map_y][map_x] == WALL || m_map[map_y][map_x] == SWITCH)
		{
			if (m_player->GetPosY() + m_player->GetGrpH() > map_y * CHIPSIZE)
			{
				//プレイヤーが普通の状態
				if (PLAYER_DEFAULT)
					m_player->SetPosY((map_y - 1)*CHIPSIZE);
				//プレイヤーが横長の状態
				else if (PLAYER_HORIZONTAL)
					m_player->SetPosY(((float)map_y - HALF_UP)*CHIPSIZE);
				//プレイヤーが縦長の状態
				else if(PLAYER_VERTICAL)
					m_player->SetPosY((map_y - 1)*CHIPSIZE);
				m_player->SetSpdY(0);
				m_player->Ground();
			}

		}
		//マップチップが縦長の壁の時
		if (m_map[map_y][map_x] == VERTICALWALL)
		{
			if (m_player->GetPosY() + m_player->GetGrpH() > map_y * CHIPSIZE)
			{
				//プレイヤーが普通の状態
				if (PLAYER_DEFAULT)
				{
					m_player->SetPosY((map_y - 1)*CHIPSIZE);
					m_player->SetSpdY(0);
					m_player->Ground();
				}
				//プレイヤーが横長の状態
				else if (PLAYER_HORIZONTAL)
				{
					m_player->SetPosY(((float)map_y - HALF_UP)*CHIPSIZE);
					m_player->SetSpdY(0);
					m_player->Ground();
				}
			}

		}

	}
	//右下
	map_x = floor((m_player->GetPosX() + m_player->GetGrpW() - SHIFTED_POS) / CHIPSIZE);
	map_y = floor((m_player->GetPosY() + m_player->GetGrpH()) / CHIPSIZE);
	if ((map_x >= 0 && map_x < MAP_WIDTH) && (map_y >= 0 && map_y < MAP_HEIGHT))
	{
		//マップチップが壁またはスイッチの時
		if (m_map[map_y][map_x] == WALL || m_map[map_y][map_x] == SWITCH)
		{
			if (m_player->GetPosY() + m_player->GetGrpH() > map_y * CHIPSIZE)
			{
				//プレイヤーが普通の状態
				if (PLAYER_DEFAULT)
					m_player->SetPosY((map_y - 1) * CHIPSIZE);
				//プレイヤーが横長の状態
				else if (PLAYER_HORIZONTAL)
					m_player->SetPosY(((float)map_y - HALF_UP) * CHIPSIZE);
				//プレイヤーが縦長の状態
				if (PLAYER_VERTICAL)
					m_player->SetPosY((map_y - 1) * CHIPSIZE);
				m_player->SetSpdY(0);
				m_player->Ground();
			}
		}
		//マップチップが縦長の壁の時
		if (m_map[map_y][map_x] == VERTICALWALL)
		{
			if (m_player->GetPosY() + m_player->GetGrpH() > map_y * CHIPSIZE)
			{
				//プレイヤーが普通の状態
				if (PLAYER_DEFAULT)
				{
					m_player->SetPosY((map_y - 1) * CHIPSIZE);
					m_player->SetSpdY(0);
					m_player->Ground();
				}
				//プレイヤーが横長の状態
				else if (PLAYER_HORIZONTAL)
				{
					m_player->SetPosY(((float)map_y - HALF_UP) * CHIPSIZE);
					m_player->SetSpdY(0);
					m_player->Ground();
				}
			}
		}
	}
}
//----------------------------------------------------------------------
//! @brief マップチップとの横の当たり判定
//!
//! @param[in] m_player
//!
//! @return なし
//----------------------------------------------------------------------

void Stage::MapSideDecison()
{
	int map_x;
	int map_y;
	//左中心
	map_x = (int)floor((m_player->GetPosX() + m_player->GetGrpW()) / CHIPSIZE);
	map_y = (int)floor((m_player->GetPosY() + m_player->GetGrpH() / 2) / CHIPSIZE);
	if ((map_x >= 0 && map_x < MAP_WIDTH) && (map_y >= 0 && map_y < MAP_HEIGHT))
	{
		//マップチップが壁の時
		if (m_map[map_y][map_x] == WALL)
		{
			if (m_player->GetPosX() + m_player->GetGrpW() >= map_x * CHIPSIZE)
			{
				//プレイヤーが普通の状態
				if (PLAYER_DEFAULT)
					m_player->SetPosX((map_x - 1)* CHIPSIZE);
				//プレイヤーが横長の状態
				if (PLAYER_HORIZONTAL)
					m_player->SetPosX((map_x - 1)* CHIPSIZE);
				//プレイヤーが縦長の状態
				else if (PLAYER_VERTICAL)
					m_player->SetPosX(((float)map_x - HALF_UP)* CHIPSIZE);
				m_player->SetSpdX(0);
			}
		}
		//マップチップが横長の壁の時
		if (m_map[map_y][map_x] == HORIZONTALWALL)
		{
				if (m_player->GetPosX() + m_player->GetGrpW() >= map_x * CHIPSIZE)
				{
					//プレイヤーが普通の状態
					if (PLAYER_DEFAULT)
						m_player->SetPosX((map_x - 1)* CHIPSIZE);
					//プレイヤーが縦長の状態
					else if (PLAYER_VERTICAL)
						m_player->SetPosX(((float)map_x - HALF_UP)* CHIPSIZE);
					m_player->SetSpdX(0);
				}
		}
		//マップチップが縦長の壁の時
		if (m_map[map_y][map_x] == VERTICALWALL)
		{
			if (m_player->GetPosX() + m_player->GetGrpW() >= map_x * CHIPSIZE)
			{
				//プレイヤーが縦長の状態
				if (PLAYER_VERTICAL)
					m_player->SetPosX(((float)map_x - HALF_UP)* CHIPSIZE);
				m_player->SetSpdX(0);
			}
		}

	}
	//右中心
	map_x = (int)floor((m_player->GetPosX()) / CHIPSIZE);
	map_y = (int)floor((m_player->GetPosY() + m_player->GetGrpH() / 2) / CHIPSIZE);
	if ((map_x >= 0 && map_x < MAP_WIDTH) && (map_y >= 0 && map_y < MAP_HEIGHT))
	{
		//マップチップが壁の時
		if (m_map[map_y][map_x] == WALL)
		{
			if (m_player->GetPosX() <= map_x* CHIPSIZE + CHIPSIZE)
			{
				m_player->SetPosX((map_x + 1)* CHIPSIZE);
				m_player->SetSpdX(0);
				m_press_flag = true;
			}
		}
		//マップチップが横長の壁の時
		if (m_map[map_y][map_x] == HORIZONTALWALL)
		{
			if (m_player->GetPosX() <= map_x* CHIPSIZE + CHIPSIZE)
			{
				//プレイヤーが普通の状態
				if (PLAYER_DEFAULT)
					m_player->SetPosX((map_x + 1)* CHIPSIZE);
				//プレイヤーが横長の状態
				if (PLAYER_VERTICAL)
					m_player->SetPosX((map_x + 1)* CHIPSIZE);
				m_player->SetSpdX(0);
			}
		}
		//マップチップが縦長の壁の時
		if (m_map[map_y][map_x] == VERTICALWALL)
		{
			if (m_player->GetPosX() <= map_x* CHIPSIZE + CHIPSIZE)
			{
				//プレイヤーが縦長の状態
				if (PLAYER_VERTICAL)
					m_player->SetPosX((map_x - HALF_UP)* CHIPSIZE);
				m_player->SetSpdX(0);
			}
		}
	}
}
//----------------------------------------------------------------------
//! @brief マップチップとの上の当たり判定
//!
//! @param[in] m_player
//!
//! @return なし
//----------------------------------------------------------------------
void Stage::MapJumpDecison()
{
	int map_x;
	int map_y;
	//左上
	map_x = ((int)floor((m_player->GetPosX() + SHIFTED_POS / 2) / CHIPSIZE));
	map_y = ((int)floor(m_player->GetPosY() / CHIPSIZE));
	//配列内かチェック
	if ((map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT))
	{
		//マップチップが壁の時
		if (m_map[map_y][map_x] == WALL)
		{
			//判定
			if ((m_player->GetPosY()) >(map_y * CHIPSIZE))
			{
				m_player->SetPosY((map_y + 1) * CHIPSIZE);
				m_player->SetSpdY(0);
			}
		}
		//マップチップが横長の壁の時
		if (m_map[map_y][map_x] == HORIZONTALWALL)
		{
			//判定
			if ((m_player->GetPosY()) >(map_y * CHIPSIZE))
			{
				//プレイヤーが普通の状態
				if (PLAYER_DEFAULT)
					m_player->SetPosY((map_y + 1) * CHIPSIZE);
				//プレイヤーが横長の状態
				else if (PLAYER_HORIZONTAL)
					m_player->SetPosY(((float)map_y + HALF_UP) * CHIPSIZE);
				m_player->SetSpdY(0);
			}
		}

	}
	//右上
	map_x = ((int)floor((m_player->GetPosX() + m_player->GetGrpW() - SHIFTED_POS / 2) / CHIPSIZE));
	map_y = ((int)floor(m_player->GetPosY() / CHIPSIZE));
	//配列内かチェック
	if ((map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT))
	{
		//マップチップが壁の時
		if (m_map[map_y][map_x] == WALL)
		{
			//判定
			if ((m_player->GetPosY()) >(map_y * CHIPSIZE))
			{
				m_player->SetPosY((map_y + 1)* CHIPSIZE);
				m_player->SetSpdY(0);
			}
		}
		//マップチップが横長の壁の時
		if (m_map[map_y][map_x] == HORIZONTALWALL)
		{
			//判定
			if ((m_player->GetPosY()) >(map_y * CHIPSIZE))
			{
				//プレイヤーが普通の状態
				if (PLAYER_DEFAULT)
					m_player->SetPosY((map_y + 1)* CHIPSIZE);
				//プレイヤーが横長の状態
				else if (PLAYER_HORIZONTAL)
					m_player->SetPosY(((float)map_y + HALF_UP)* CHIPSIZE);
				m_player->SetSpdY(0);
			}
		}
	}
}


//----------------------------------------------------------------------
//! @brief スイッチとプレイヤーの当たり判定
//!
//! @param[in] 比較をするオブジェクトを２つ
//!
//! @return 当たっているとき１、当たっていないとき０
//----------------------------------------------------------------------
bool Stage::CollisionSwitch()
{
	float x1;
	float r1;
	if (PLAYER_VERTICAL)	//プレイヤーが縦長だったら
	{
		 x1 = m_player->GetPosX() + m_player->GetGrpW();	//Aの中心座標x
		 r1 = m_player->GetGrpW();	
	}
	else
	{
		x1 = m_player->GetPosX() + m_player->GetGrpW() / 2;	//Aの中心座標x
		r1 = m_player->GetGrpW() / 2;
	}
	
	float y1 = m_player->GetPosY() + m_player->GetGrpH() / 2;	//Aの中心座標y
	float x2 = m_switch->GetPosX() + m_switch->GetGrpW() / 2;	//Bの中心座標x
	float y2 = m_switch->GetPosY() + m_switch->GetGrpH() / 2;	//Bの中心座標y
	float r2 = m_switch->GetGrpW() / 2;
	//円の当たり判定
	if ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) <= (r1 + r2)*(r1 + r2))
	{
		m_switch->SetState(true);
		return true;
	}
	return false;
}


//----------------------------------------------------------------------
//! @brief 風とプレイヤーの当たり判定
//!
//! @param[in] 比較をするオブジェクトを２つ
//!
//! @return 当たっているとき１、当たっていないとき０
//----------------------------------------------------------------------
void Stage::CollisionWind()
{
	int loop_grp_h = 0;
	int loop_grp_h2 = 0;
	int map_x;
	int map_y[WIND_RANGE];
	int one_map_y;
	
	//左下
	map_x = floor((m_player->GetPosX() + SHIFTED_POS) / CHIPSIZE);
	one_map_y = floor((m_player->GetPosY() + m_player->GetGrpH()) / CHIPSIZE);
	for (int i = 0; i < WIND_RANGE; i++)
	{
		loop_grp_h += m_player->GetGrpH();
		map_y[i] = floor((m_player->GetPosY() + loop_grp_h) / CHIPSIZE);
		if ((map_x >= 0 && map_x < MAP_WIDTH) && (map_y[i] >= 0 && map_y[i] < MAP_HEIGHT))
		{
			//マップチップが壁またはスイッチの時
			if (m_map[map_y[i]+2][map_x] == WIND)
			{
				if (m_player->GetPosY() + m_player->GetGrpH() > map_y[i] * CHIPSIZE)
				{
					////プレイヤーが普通の状態
					//if (PLAYER_DEFAULT)
					//	m_player->SetPosY((one_map_y - 1)*CHIPSIZE);
					//プレイヤーが横長の状態
					if (PLAYER_HORIZONTAL)
					{
						m_player->SetPosY(((float)map_y[i] - HALF_UP - 3) * CHIPSIZE);
					
					//プレイヤーが縦長の状態
					//else if (PLAYER_VERTICAL)
					//	m_player->SetPosY((one_map_y - 1) * CHIPSIZE);
					m_player->SetSpdY(0);
					m_player->Ground();
					}
				}

			}
		}
	}
	
	
	//右下
	map_x = floor((m_player->GetPosX() + m_player->GetGrpW() - SHIFTED_POS) / CHIPSIZE);
	one_map_y = floor((m_player->GetPosY() + m_player->GetGrpH()) / CHIPSIZE);
	for (int i = 0; i < WIND_RANGE; i++)
	{
		loop_grp_h2 += m_player->GetGrpH();
		map_y[i] = floor((m_player->GetPosY() + loop_grp_h2) / CHIPSIZE);
		if ((map_x >= 0 && map_x < MAP_WIDTH) && (map_y >= 0 && map_y[i] < MAP_HEIGHT))
		{
			//マップチップが壁またはスイッチの時
			if (m_map[map_y[i]+2][map_x] == WIND)
			{
				if (m_player->GetPosY() + m_player->GetGrpH() > map_y[i] * CHIPSIZE)
				{
					////プレイヤーが普通の状態
					//if (PLAYER_DEFAULT)
					//	m_player->SetPosY((one_map_y - 1) * CHIPSIZE);
					//プレイヤーが横長の状態
					if (PLAYER_HORIZONTAL)
					{
						m_player->SetPosY(((float)map_y[i] - HALF_UP - 3) * CHIPSIZE);
					
					////プレイヤーが縦長の状態
					//else if (PLAYER_VERTICAL)
					//	m_player->SetPosY((one_map_y - 1)*CHIPSIZE);
					m_player->SetSpdY(0);
					m_player->Ground();
					}
				}
			}
		}
	}

}

//----------------------------------------------------------------------
//! @brief プレス機とプレイヤーの当たり判定
//!
//! @param[in] なし
//!
//! @return 当たっているかどうか
//----------------------------------------------------------------------
void Stage::CollisionPress()
{
	for (int i = 0; i < m_press_count; i++)
	{
		//左
		if (m_player->GetPosY() > m_press[i]->GetPosY() &&
			m_press[i]->GetPosY() + m_press[i]->GetGrpH() > m_player->GetPosY() + m_player->GetGrpH() &&
			m_player->GetPosX() + m_player->GetGrpW() > m_press[i]->GetPosX() &&
			m_player->GetPosX() < m_press[i]->GetPosX())
		{
			m_player->SetPosX(m_press[i]->GetPosX() - m_player->GetGrpW());	//座標
			m_player->SetSpdX(0);	//スピード
		}
		//右
		if (m_player->GetPosY() > m_press[i]->GetPosY() &&
			m_press[i]->GetPosY() + m_press[i]->GetGrpH() > m_player->GetPosY() + m_player->GetGrpH() &&
			m_player->GetPosX() < m_press[i]->GetPosX() + m_press[i]->GetGrpW() &&
			m_player->GetPosX() + m_player->GetGrpW() > m_press[i]->GetPosX() + m_press[i]->GetGrpW())
		{
			m_player->SetPosX(m_press[i]->GetPosX() + m_press[i]->GetGrpW());	//座標
			m_player->SetSpdX(0);	//スピード
		}
		//下
		else if (m_player->GetPosX() + m_player->GetGrpW() > m_press[i]->GetPosX() &&
			m_press[i]->GetPosX() + m_press[i]->GetGrpW() > m_player->GetPosX() &&
			m_press[i]->GetPosY() + m_press[i]->GetGrpH() > m_player->GetPosY())
		{
			m_player->SetPosY(m_press[i]->GetPosY() + m_press[i]->GetGrpH());	//座標
			m_player->SetSpdY(0);	//スピード
			//ジャンプしていないなら
			if (!m_player->GetJump())
				m_player->ChangePlayerH();	//潰す
		}
	}
}

//----------------------------------------------------------------------
//! @brief 横のプレス機とプレイヤーの当たり判定
//!
//! @param[in] なし
//!
//! @return 当たっているかどうか
//----------------------------------------------------------------------
void Stage::CollisionSidePress()
{
	for (int i = 0; i < m_side_press_count; i++)
	{
		//左
		if (m_player->GetPosX() + m_player->GetGrpW() > m_side_press[i]->GetPosX() &&
			m_player->GetPosY() > m_side_press[i]->GetPosY() &&
			m_side_press[i]->GetPosY() + m_side_press[i]->GetGrpH() >= m_player->GetPosY() + m_player->GetGrpH() &&
			m_side_press[i]->GetPosX() > m_player->GetPosX())
		{
			m_player->SetPosX(m_side_press[i]->GetPosX() - m_player->GetGrpW());	//座標
			m_player->SetSpdX(0);	//スピード
			if(m_press_flag)
			m_player->ChangePlayerW();	//潰す
		}
		//上
		if (m_player->GetPosX() + m_player->GetGrpW() > m_side_press[i]->GetPosX() &&
			m_side_press[i]->GetPosX() + m_side_press[i]->GetGrpW() > m_player->GetPosX() &&
			m_player->GetPosY() + m_player->GetGrpH() > m_side_press[i]->GetPosY())
		{
			m_player->SetPosY(m_side_press[i]->GetPosY() - m_player->GetGrpH());
			m_player->SetSpdY(0);
			m_player->Ground();
		}
	}
}

//----------------------------------------------------------------------
//! @brief　プレイヤーとバーナーとの当たり判定
//!
//! @param[in] なし
//!
//! @return false:当たっていない, true:当たっている
//----------------------------------------------------------------------
bool Stage::CollisionBurner(int i)
{
	//	短形での当たり判定
	if (
		(m_player->GetPosX() <= m_burner[i]->GetPosX() + m_burner[i]->GetGrpW()) &&
		(m_player->GetPosX() + m_player->GetGrpW() >= m_burner[i]->GetPosX()) &&
		(m_player->GetPosY() <= m_burner[i]->GetPosY() + m_burner[i]->GetGrpH()) &&
		(m_player->GetPosY() + m_player->GetGrpH() >= m_burner[i]->GetPosY())
		)
	{
		return true;
	}

	return false;
}

//----------------------------------------------------------------------
//! @brief　プレイヤーと水との当たり判定
//!
//! @param[in] なし
//!
//! @return false:当たっていない, true:当たっている
//----------------------------------------------------------------------
bool Stage::CollisionWater(int i)
{
	//	短形での当たり判定
	if (
		(m_player->GetPosX() <= m_water[i]->GetPosX() + m_water[i]->GetGrpW()) &&
		(m_player->GetPosX() + m_player->GetGrpW() >= m_water[i]->GetPosX()) &&
		(m_player->GetPosY() <= m_water[i]->GetPosY() + m_water[i]->GetGrpH()) &&
		(m_player->GetPosY() + m_player->GetGrpH() >= m_water[i]->GetPosY())
		)
	{
		return true;
	}

	return false;
}

//----------------------------------------------------------------------
//! @brief　プレイヤーとゴールとの当たり判定
//!
//! @param[in] なし
//!
//! @return false:当たっていない, true:当たっている
//----------------------------------------------------------------------
bool Stage::CollisionGoal()
{
	//	短形での当たり判定
	if (
		(m_player->GetPosX() <= m_goal->GetPosX() + m_goal->GetGrpW()) &&
		(m_player->GetPosX() + m_player->GetGrpW() >= m_goal->GetPosX()) &&
		(m_player->GetPosY() <= m_goal->GetPosY() + m_goal->GetGrpH()) &&
		(m_player->GetPosY() + m_player->GetGrpH() >= m_goal->GetPosY())
		)
	{
		return true;
	}

	return false;
}

//----------------------------------------------------------------------
//! @brief　プレイヤーがマップから落ちた時の判定
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Stage::DownMapPlayer()
{
	if (m_player->GetPosY() > MAP_SIZE_HEIGHT)		//プレイヤーが画面下に行ったら
	{
		g_NextScene = OVER;
	}
}