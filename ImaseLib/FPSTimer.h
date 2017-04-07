//--------------------------------------------------------------------------------------
// File: FPSTimer.h
//
// FPS制御をするクラス
//
// 使い方：WaitFrame関数でフレーム更新のタイミングを調整します
//         処理落ちが発生した場合は直ちにWaitFrame関数から抜けます
//		   ※このバージョンは描画スキップなどは考えていません
//
// Date: 2015.2.16
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include <Windows.h>

namespace ImaseLib
{
	class FPSTimer
	{
	private:

#pragma region
		LARGE_INTEGER m_freq;	// 高分解能パフォーマンスカウンタの周波数
		int m_fps;				// FPS（１秒あたりのフレーム数）
		DWORD m_fpsWait;		// fpsWait = 1000 * 0x10000 / fps
		DWORD m_fpsWaitTT;		// fpsWaitの少数部分の誤差を入れる変数
		DWORD m_lastDrawTime;	// 最後に描画した時間

		// FPS計測用変数
		int m_nowFPS;
		int m_frames;
		DWORD m_beforeTime;

		// 現在の時間を取得する
		DWORD GetNowTime();
#pragma endregion

	public:

		// 引数にFPS（１秒間あたりのフレーム数）を指定する
		FPSTimer(int fps);

		// 設定されているFPSを取得する
		int GetFPS();

		// FPSを変更する
		void SetFPS(int fps);

		// 次のフレームまで待つための関数
		void WaitFrame();

		// 現在のFPSを取得する
		int GetNowFPS();

	};
}
