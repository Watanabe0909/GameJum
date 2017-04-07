//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameBase.h
//!
//! @brief  ゲームの基本のヘッダファイル
//!
//! @date   2016/12/16
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

class GameBase
{
public:
	virtual ~GameBase() {};
	virtual void Update() = 0;
	virtual void Render() = 0;
};
