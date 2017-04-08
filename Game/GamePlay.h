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
<<<<<<< HEAD
#include "Object\Press.h"
=======
#include "MoveBlock.h"

>>>>>>> 592c7ff96f3a6235e62b19fc2ccbf2838140ca34
//クラス
class Play:public GameBase
{
private:
<<<<<<< HEAD
	Stage* m_stage;
	//Press* m_press;
=======
	Stage m_stage;
	Moveblock* m_moveblock;
>>>>>>> 592c7ff96f3a6235e62b19fc2ccbf2838140ca34
public:
	Play();				//	コンストラクタ
	~Play();			//	デストラクタ
	void Update();		//	更新処理
	void Render();		//	描画処理

};
