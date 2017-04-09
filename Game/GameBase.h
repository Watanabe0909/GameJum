//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameBase.h
//!
//! @brief  ゲームの基本のヘッダファイル
//!
//! @date   2017/04/08
//!
//! @author 加藤 竜哉
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

class GameBase
{
public:
	virtual ~GameBase() {};
	virtual void Update() = 0;
	virtual void Render() = 0;
};
