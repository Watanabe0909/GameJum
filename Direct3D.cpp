//--------------------------------------------------------------------------------------
// File: Direct3D.cpp
//
// Direct3Dに関する関数群
//
// 備考：このプログラムはDirect3Dを使用するための処理を関数化したサンプルです
//
// Date: 2015.6.24
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------

#include <DirectXColors.h>
#include "Direct3D.h"

using namespace Microsoft::WRL;

//////////////////////////////////
// リンクするライブラリ指定		//
//////////////////////////////////
#pragma comment(lib, "d3d11.lib")

//////////////////////
// グローバル変数	//
//////////////////////
BOOL								g_fullScreen = FALSE;					// フルスクリーンで起動する場合はTRUEを指定する
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;	// ドライバータイプ（ハードウェアなど）
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;// 機能レベル
ComPtr<ID3D11Device>                g_pd3dDevice;							// DirectX11のデバイス
ComPtr<ID3D11DeviceContext>         g_pImmediateContext;					// コンテキスト
ComPtr<IDXGISwapChain>              g_pSwapChain;							// スワップチェイン
ComPtr<ID3D11RenderTargetView>      g_pRenderTargetView;					// レンダーターゲットビュー
ComPtr<ID3D11Texture2D>             g_pDepthStencil;						// 深度ステンシル
ComPtr<ID3D11DepthStencilView>      g_pDepthStencilView;					// 深度ステンシルビュー

//--------------------------------------------------------------------------------------
// DirectXデバイスの初期化
//--------------------------------------------------------------------------------------
HRESULT Direct3D_InitDevice(HWND hWnd)
{
	HRESULT hr = S_OK;

	// クライアント領域の取得
	RECT rc;
	GetClientRect(hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;	// デバックレイヤーをサポートするフラグ
	createDeviceFlags |= 0;	// デバックレイヤーをサポートするフラグ
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	// スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;	// <--リフレッシュレートはDXGIの自動設定に任せる
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = !g_fullScreen;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // <--フルスクリーンへの切り替えの時に表示モードを変更する

	//////////////////////////////////////
	// デバイスとスワップチェーンの作成	//
	//////////////////////////////////////
	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(nullptr, g_driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	//////////////////////////////////////////////////
	// Atl+Enterで画面モードを変更しないようにする	//
	//////////////////////////////////////////////////
	ComPtr<IDXGIDevice1> pDXGIDevice;
	ComPtr<IDXGIAdapter> pDXGIAdapter;
	ComPtr<IDXGIFactory> pDXGIFactory;

	// インターフェイス取得
	hr = g_pd3dDevice.As(&pDXGIDevice);
	if (FAILED(hr)) {
		return hr;
	}

	// アダプター取得
	hr = pDXGIDevice->GetAdapter(&pDXGIAdapter);
	if (FAILED(hr)) {
		return hr;
	}
	// ファクトリー取得
	hr = pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (LPVOID*)&pDXGIFactory);
	if (FAILED(hr)) {
		return hr;
	}
	// 画面モードの切り替え機能の設定
	hr = pDXGIFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_WINDOW_CHANGES);
	if (FAILED(hr)) {
		return hr;
	}

	//////////////////////////
	// バックバッファの作成	//
	//////////////////////////
	hr = Direct3D_InitBackBuffer();
	if (FAILED(hr))
		return hr;

	//////////////////////
	// ビューポート作成	//
	//////////////////////
	CD3D11_VIEWPORT vp(0.0f, 0.0f, (FLOAT)width, (FLOAT)height);
	g_pImmediateContext->RSSetViewports(1, &vp);

	return S_OK;
}

//--------------------------------------------------------------------------------------
// バックバッファと深度バッファの設定
//--------------------------------------------------------------------------------------
HRESULT Direct3D_InitBackBuffer()
{
	HRESULT hr = S_OK;

	//////////////////////////
	// バックバッファの作成	//
	//////////////////////////

	// スワップチェーンからバックバッファを取得
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	// バックバッファに指定されているテクスチャ情報を取得
	D3D11_TEXTURE2D_DESC descBackBuffer;
	pBackBuffer->GetDesc(&descBackBuffer);

	// レンダーターゲットビューを作成
	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, g_pRenderTargetView.GetAddressOf());
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	//////////////////////////
	// 深度バッファの作成	//
	//////////////////////////

	// 深度ステンシルテクスチャの作成
	CD3D11_TEXTURE2D_DESC descDepth(descBackBuffer);	// <--バックバッファに指定されているテクスチャ情報を元に設定する
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = g_pd3dDevice->CreateTexture2D(&descDepth, nullptr, &g_pDepthStencil);
	if (FAILED(hr))
		return hr;

	// 深度ステンシルビューの作成
	CD3D11_DEPTH_STENCIL_VIEW_DESC descDSV(D3D11_DSV_DIMENSION_TEXTURE2D, descDepth.Format);
	hr = g_pd3dDevice->CreateDepthStencilView(g_pDepthStencil.Get(), &descDSV, &g_pDepthStencilView);
	if (FAILED(hr))
		return hr;

	//////////////////////////////
	// レンダーターゲット設定	//
	//////////////////////////////
	g_pImmediateContext->OMSetRenderTargets(1, g_pRenderTargetView.GetAddressOf(), g_pDepthStencilView.Get());

	return S_OK;
}

//--------------------------------------------------------------------------------------
// DirectXデバイス周りの終了処理
//--------------------------------------------------------------------------------------
void Direct3D_CleanupDevice()
{
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
}

