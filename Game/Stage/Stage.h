//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Stage.h
//!
//! @brief  ステージ処理のヘッダファイル
//!
//! @date   2017/04/07
//!
//! @author 佐久間尚輝
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

//インクルード
#include <string>
#include "..\ObjectBase.h"
#include "..\Object\Press.h"
#include "..\Object\SidePress.h"
#include "..\Object\Burner.h"
#include "..\Object\Water.h"
#include "..\Switch.h"
#include "..\Wind.h"
#include "..\Object\Goal.h"
#include "..\Object\SidePress.h"
#include "..\Player.h"
#include "..\Camera.h"

#define PLAYER_DEFAULT (m_player->GetGrpH() == CHIPSIZE && m_player->GetGrpW() == CHIPSIZE)			//普通の状態
#define PLAYER_VERTICAL (m_player->GetGrpH() == CHIPSIZE && m_player->GetGrpW() == CHIPSIZE / 2)	//縦長
#define PLAYER_HORIZONTAL (m_player->GetGrpH() == CHIPSIZE / 2 && m_player->GetGrpW() == CHIPSIZE)	//横長
//クラスの呼び出し
class Texture;

//enum
enum Map
{
	NONE,			//何もなし
	BACKGROUND,		//背景
	WALL,			//壁
	HORIZONTALWALL,	//横長の壁
	VERTICALWALL,	//縦長の壁
	WATER,			//水
	PRESS,			//プレス機
	SIDEPRESS,		//横のプレス機
	BURNER,			//バーナー
	PLAYER,			//プレイヤー	
	GOAL,			//ゴール
	SWITCH,			//スイッチ
	WIND,			//風		
};

class Stage 
{
private:
	static const int  MAP_WIDTH = 90;		//マップの横幅
	static const int MAP_HEIGHT = 15;		//マップの縦幅
	static const int MAX_TIP = 1350;		//マップチップの数
	static const int CHIPSIZE = 32;			//マップチップの大きさ
	static const int MAX_PRESS_NUM = 5;		//プレス機の数
	static const int MAX_BURNER_NUM = 6;	//バーナーの数
	static const int MAX_WATER_NUM = 5;		//水のオブジェクト数
	static const int SHIFTED_POS = 10;		//座標をズラす
	static const int SCREEN_WIDTH = 640;	//画面の幅
	static const float HALF_UP;				//半分上げる
	static const int MAX_WIND_NUM = 6;		//プレス機の数
	static const int WIND_RANGE = 6;		//風の範囲
	int m_map[MAP_HEIGHT][MAP_WIDTH];		//マップ
	Texture* m_map_image;					//マップの画像
	Press* m_press[MAX_PRESS_NUM];			//プレス機
	Burner* m_burner[MAX_BURNER_NUM];		//バーナー
	Water* m_water[MAX_WATER_NUM];			//水
	Goal* m_goal;							//ゴール
	SidePress* m_side_press[MAX_PRESS_NUM];	//横のプレス機
	Player* m_player;						//プレイヤー
	Camera* m_camera;						//カメラ
	Switch* m_switch;						//スイッチ
	Wind* m_wind[MAX_WIND_NUM];				//風
	int m_press_count;						//プレス機のカウント
	int m_burner_count;						//バーナーのカウント
	int m_water_count;						//水のオブジェクトのカウント
	int m_side_press_count;					//横のプレス機のカウント
	int m_wind_count;						//風のカウント
	bool m_press_flag;						//プレス用のフラグ
	void ImportData(std::string filename);	//csvファイルからの読み込み
public:
	Stage();								//コンストラクタ
	~Stage();								//デストラクタ
	void DrawStage();						//ステージの描画
	void Update();							//アップデート
	void ObjectDraw();						//オブジェクトの描画
	void DrawSprite(int grp_x, int grp_y, int grp_w, int grp_h, int i, int j);	//スプライトの描画
	void MapDownDecison();					//マップチップとの下の当たり判定
	void MapSideDecison();					//マップチップとの横の当たり判定
	void MapJumpDecison();					//マップチップとの上の当たり判定
	void CollisionPress();					//プレス機とプレイヤーの当たり判定
	bool CollisionBurner(int i);			//バーナーとプレイヤーの当たり判定
	bool CollisionWater(int i);				//水とプレーヤーとの当たり判定
	bool CollisionGoal();					//ゴールとプレーヤーとの当たり判定
	bool CollisionSwitch();					//スイッチとプレイヤーの当たり判定
	void CollisionWind();					//風とプレイヤーの当たり判定
	void CollisionSidePress();				//横のプレス機とプレイヤーの当たり判定
};