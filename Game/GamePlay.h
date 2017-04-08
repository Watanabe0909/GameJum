//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.h
//!
//! @brief  プレイシーンのヘッダファイル
//!
//! @date   2017/04/07
//!
//! @author 加藤 竜哉
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//	多重インクルードの防止
#pragma once
//	ヘッダファイルのインクルード
#include "GameBase.h"

//クラス
class Play:public GameBase
{
private:
	Texture *m_back_image;		//	背景画像
	Texture *m_pause_image;		//	ポーズ時画像
	Texture *m_line_image;		//	選択用線の画像
	bool m_pause_flag;			//	ポーズフラグ
	int m_pause_select;			//	ポーズ時選択用変数

	const int RETURN = 0;		//	ゲームに戻るときの定数
	const int RETURN_TITLE = 1; //	タイトルに戻るときの定数

public:
	Play();						//	コンストラクタ
	~Play();					//	デストラクタ
	void Update();				//	更新処理
	void Render();				//	描画処理
};
