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
	static const int PLAYER_HALF_PIC = 80;	//画像の半分
	static const int PLAYER_GRAVITY = 1;//重力
	static const float PLAYER_HALF_GRAVITY; //半分の重力
	static const int PLAYER_MOVE_POW = 3;//移動力
	static const int PLAYER_JUMP_POW = -15;//ジャンプ力
	bool m_jump_flag;	//ジャンプ
	bool m_left_flag;
	bool m_right_flag;
public:
	Player(int pos_x, int pos_y);	//コンストラクタ
	~Player();			//デストラクタ
	void Move();		//移動
	void Ground();		//地面についている
	void ChangePlayerH();//プレイヤーの高さを変える
	void ChangePlayerW();//プレイヤーの幅を変える
	bool GetJump();		//ジャンプしているかどうか
};
