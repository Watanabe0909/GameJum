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
#include "Game\ObjectBase.h"
//クラスの呼び出し
class Texture;

class Stage final :public ObjectBase
{
private:
	static const int  MAP_WIDTH = 20;	//マップの横幅
	static const int MAP_HEIGHT = 15;	//マップの縦幅
	static const int MAX_TIP = 300;		//マップチップの数
	int g_map[MAP_HEIGHT][MAP_WIDTH];	//マップ
public:
	Stage();			//コンストラクタ
	~Stage();			//デストラクタ
	void DrawStage();	//ステージの描画
	void importData(std::string filename);	//csvファイルからの読み込み

};