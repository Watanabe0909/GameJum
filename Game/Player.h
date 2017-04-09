//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.h
//!
//! @brief  プレイヤー処理のヘッダファイル
//!
//! @date   2017/04/09
//!
//! @author 佐久間尚輝
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

#include "ObjectBase.h"

class Player :public ObjectBase
{
private:
	static const int PLAYER_GRP = 32;	//元画像のGRP
	static const int PLAYER_GRAVITY = 1;//重力
	static const int PLAYER_MOVE_POW = 3;//移動力
	static const int PLAYER_JUMP_POW = -15;//ジャンプ力
	bool m_jump_flag;	//ジャンプ
public:
	Player(int pos_x, int pos_y);	//コンストラクタ
	~Player();			//デストラクタ
	void Move();		//移動
	void Ground();		//地面についている
	void ChangePlayer();//プレイヤーの大きさを変える
};
