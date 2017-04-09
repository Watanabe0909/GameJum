//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameTitle.h
//!
//! @brief  タイトルシーンのヘッダファイル
//!
//! @date   2017/04/07
//!
//! @author 加藤 竜哉
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//	多重インクルードの防止
#pragma once
//	ヘッダファイルのインクルード
#include "GameBase.h"

class Title:public GameBase
{
private:
	Texture *m_title_image;					//	タイトル画像
	Texture *m_title_image2;				//	タイトル画像２
	bool m_fade_flag;						//	フェード用フラグ				
	DirectX::SimpleMath::Color color;		//	フェード用変数
	float m_alfa;							//	画像の透明度用変数
	int m_count;							//	カウント

public:
	Title();					//	コンストラクタ
	~Title();					//	デストラクタ
	void Update();				//	更新処理
	void Render();				//	描画処理

};



