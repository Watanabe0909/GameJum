//--------------------------------------------------------------------------------------
// File: Main.cpp
//
// メイン
//
// 備考：このプログラムはDirectX11を使用するための最低必要と思われる処理を組み込んだサンプルです
//       余分な処理は記述していませんのでオリジナルフレームワークのベースに使用してください
//
// Date: 2015.8.27
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include <Windows.h>
#include <DirectXColors.h>
#include "DirectXTK.h"
#include "Direct3D.h"
#include "ImaseLib\FPSTimer.h"
#include <SimpleMath.h>
#include "Game\GameMain.h"
#include "MemoryLeakDetector.h"

using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;
using namespace DirectX;

//////////////////
// 定数宣言		//
//////////////////
// ウインドウスタイル
static const DWORD WINDOW_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

// 画面解像度
static const int WINDOW_W = 640;
static const int WINDOW_H = 480;

//////////////////////////////
// 関数のプロトタイプ宣言	//
//////////////////////////////
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//////////////////////
// グローバル変数	//
//////////////////////
HINSTANCE g_hInst = nullptr;	// インスタンスハンドル
HWND g_hWnd = nullptr;	// ウインドウハンドル

//--------------------------------------------------------------------------------------
// メイン
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//メモリリーク検出
	SetUpMemoryLeakDetector();

	// 1秒間に60フレームで固定する
	ImaseLib::FPSTimer fpsTimer(60);

	// ウインドウの作成
	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;

	// DirectXデバイスの初期化
	if (FAILED(Direct3D_InitDevice(g_hWnd)))
	{
		// 初期化に失敗
		Direct3D_CleanupDevice();
		return 0;
	}

	// DirectXTK関係の初期化
	DirectXTK_Initialize();


	InitializeGame();		//ゲームの初期化処理


	// メインループ
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		int fps = fpsTimer.GetNowFPS();
		wchar_t buf[16];
		swprintf_s(buf, 16, L"fps = %d", fps);

		// メッセージが来ているか調べる
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// メッセージが来ていればウインドウプロシージャへ送る
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// キー入力やマウス情報の更新
			DirectXTK_UpdateInputState();

			if (g_keyTracker->pressed.Escape)
			{
				break;
			}

			UpdateGame();		//ゲームの更新処理


			// バックバッファのクリア
			g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView.Get(), DirectX::Colors::MidnightBlue);

			// 深度バッファのクリア
			g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

			//---------- ここで描画コマンドを発行する　---------//
			g_spriteBatch->Begin(SpriteSortMode_Deferred, g_pCommonStates->NonPremultiplied(), g_pCommonStates->PointClamp());


			RenderGame();		//ゲームの描画処理


			// fpsの表示
			//g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(0, 0));

			g_spriteBatch->End();

			// 画面更新を待つ
			fpsTimer.WaitFrame();

			// バックバッファとフロントバッファを入れ替える
			g_pSwapChain->Present(0, 0);
		}
	}


	FinalizeGame();		//ゲームの後始末処理


	// DirectXデバイス周りの終了処理
	Direct3D_CleanupDevice();

	return 0;
}

//--------------------------------------------------------------------------------------
// ウインドウの作成
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// ウインドウクラスを登録する
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)NULL);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"WindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)NULL);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// ウインドウを作成する
	g_hInst = hInstance;
	RECT rc = { 0, 0, WINDOW_W, WINDOW_H };	// ←ウインドウサイズ
	AdjustWindowRect(&rc, WINDOW_STYLE, FALSE);
	g_hWnd = CreateWindow(L"WindowClass", L"サンプルフレームワーク", WINDOW_STYLE,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!g_hWnd)
		return E_FAIL;

	// ウインドウの表示
	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}

//--------------------------------------------------------------------------------------
// ウインドウプロシージャー
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:		// ウインドウが破棄されたメッセージ
		PostQuitMessage(0);	// WM_QUITメッセージを送出する（メインループを抜ける）
		break;

	case WM_ACTIVATEAPP:	// ウインドウがアクティブ化、非アクティブ化する時に来るメッセージ
		Keyboard::ProcessMessage(message, wParam, lParam);
		Mouse::ProcessMessage(message, wParam, lParam);
		break;

	case WM_KEYDOWN:		// キー入力関係のメッセージ
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(message, wParam, lParam);
		break;

	case WM_INPUT:			// マウス関係のメッセージ
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Mouse::ProcessMessage(message, wParam, lParam);
		break;

	default:
		// 自分で処理しないメッセージはDefWindowProc関数に任せる
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

