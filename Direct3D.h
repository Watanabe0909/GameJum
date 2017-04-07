//--------------------------------------------------------------------------------------
// File: Direct3D.h
//
// Direct3Dに関する関数群
//
// Date: 2015.6.24
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once


#include <Windows.h>
#include <wrl.h>
#include <d3d11.h>

//////////////////////////////
// 関数のプロトタイプ宣言	//
//////////////////////////////
HRESULT Direct3D_InitDevice(HWND hWnd);
HRESULT Direct3D_InitBackBuffer();
void Direct3D_CleanupDevice();

//////////////////////////////
// グローバル変数			//
//////////////////////////////
extern Microsoft::WRL::ComPtr<ID3D11Device>				g_pd3dDevice;			// DirectX11のデバイス
extern Microsoft::WRL::ComPtr<ID3D11DeviceContext>		g_pImmediateContext;	// コンテキスト
extern Microsoft::WRL::ComPtr<IDXGISwapChain>			g_pSwapChain;			// スワップチェイン
extern Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	g_pRenderTargetView;	// レンダーターゲットビュー
extern Microsoft::WRL::ComPtr<ID3D11Texture2D>			g_pDepthStencil;		// 深度ステンシル
extern Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	g_pDepthStencilView;	// 深度ステンシルビュー
