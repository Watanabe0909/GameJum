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
#include "Stage\Stage.h"
#include "Object\Press.h"
#include "Object\SidePress.h"
#include "MoveBlock.h"
//クラス
class Play:public GameBase
{
private:
	Stage* m_stage;
	Moveblock* m_moveblock;
	SidePress* m_sidepress[2];
public:
	Play();				//	コンストラクタ
	~Play();			//	デストラクタ
	void Update();		//	更新処理
	void Render();		//	描画処理

};
