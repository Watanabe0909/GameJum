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
//クラスの呼び出し
class Texture;

//enum
enum Map
{
	NONE,		//何もなし
	WALL,		//壁
	SMALLWALL,	//半分の壁
	WATER,		//水
};

class Stage 
{
private:
	static const int  MAP_WIDTH = 20;	//マップの横幅
	static const int MAP_HEIGHT = 15;	//マップの縦幅
	static const int MAX_TIP = 300;		//マップチップの数
	static const int CHIPSIZE = 32;		//マップチップの大きさ
	int m_map[MAP_HEIGHT][MAP_WIDTH];	//マップ
	Texture* m_map_image;				//マップの画像
	void ImportData(std::string filename);	//csvファイルからの読み込み 
public:
	Stage();			//コンストラクタ
	~Stage();			//デストラクタ
	void DrawStage();	//ステージの描画
	void DrawSprite(int grp_x, int grp_y, int grp_w, int grp_h, int i, int j);	//スプライトの描画
};