//--------------------------------------------------------------------------------------
// File: FPSTimer.cpp
//
// FPS制御をするクラス
//
// 使い方：WaitFrame関数でフレーム更新のタイミングを調整します
//         処理落ちが発生した場合は直ちにWaitFrame関数から抜けます
//
// 参考URL：http://sourceforge.jp/projects/nyx-lib/scm/svn/blobs/146/Nyx/branches/v4/Nyx/Source/Timer/FPSTimer.cpp
// 参考書籍：Windows プロフェッショナル ゲームプログラミング
//
// Date: 2015.2.16
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "FPSTimer.h"

using namespace ImaseLib;

FPSTimer::FPSTimer(int fps)
: m_fps(0)
, m_fpsWait(0)
, m_fpsWaitTT(0)
, m_lastDrawTime(0)
, m_nowFPS(0)
, m_frames(0)
{
	// 高分解能パフォーマンスカウンタの周波数を取得
	QueryPerformanceFrequency(&m_freq); 
	// FPSの設定
	SetFPS(fps);
}

int FPSTimer::GetFPS()
{
	return m_fps;
}

void FPSTimer::SetFPS(int fps)
{
	m_fps = fps;
	if (fps == 0)
	{
		m_fpsWait = 0;
	}
	else
	{
		// 0x00010000 が１msと考え1/60(16.66ms)をDWORD型で表現する
		m_fpsWait = 1000 * 0x10000 / fps;
	}
}

// PC起動からの経過時間を返す(ms)
DWORD FPSTimer::GetNowTime()
{
	if (m_fps == 0) return 0;

	LARGE_INTEGER time;

	QueryPerformanceCounter(&time);
	return (DWORD)((double)(time.QuadPart * 1000) / m_freq.QuadPart);
}

void FPSTimer::WaitFrame()
{
	// fpsWaitが0の場合は待たない
	if (m_fpsWait == 0) return;

	DWORD nowTime = GetNowTime();

	// fpsWaitTTには待ち時間の少数以下の情報が入っている
	m_fpsWaitTT = (m_fpsWaitTT & 0xffff) + m_fpsWait;

	// 待ち時間を求める（0x0000****上位２バイトが整数部）
	DWORD waitTime = m_fpsWaitTT >> 16;

	// 経過時間（現在の時間－描画した時間）を算出する
	DWORD elapsedTime = nowTime - m_lastDrawTime;

	// 待ち時間を経過時間が越えているので待つ必要はない
	if (elapsedTime >= waitTime)
	{
		// 描画した時間を現在の時間にして関数を抜ける
		m_lastDrawTime = nowTime;

		// 現在のFPSを取得
		if (nowTime - m_beforeTime >= 1000)
		{
			m_beforeTime = nowTime;
			m_nowFPS = m_frames;
			m_frames = 0;
		}
		m_frames++;

		return;
	}

	//////////////////////////////////////////////////////////////
	//	まだ次のフレーム更新まで時間があるので待つことにする	//
	//////////////////////////////////////////////////////////////

	// Sleep関数で待つことにするが誤差4ms以内の場合はSleepしない
	if (waitTime - elapsedTime >= 4)
	{
		Sleep(waitTime - elapsedTime - 3);
	}
	// Sleep関数で正確な待ち時間を指定できないのでここでさらにループして待つ
	while (GetNowTime() - m_lastDrawTime < waitTime);

	// waitTime時間待ったことにして、最後に描画した時間を更新
	m_lastDrawTime += waitTime;

	// 現在のFPSを取得
	if (nowTime - m_beforeTime >= 1000)
	{
		m_beforeTime = nowTime;
		m_nowFPS = m_frames;
		m_frames = 0;
	}
	m_frames++;

}

// 現在のFPS（1秒あたりのフレーム数）を取得する
int FPSTimer::GetNowFPS()
{
	return m_nowFPS;
}
