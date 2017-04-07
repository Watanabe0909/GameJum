//--------------------------------------------------------------------------------------
// File: Texture.cpp
//
// テクスチャクラス
//
// Date: 2015.9.2
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include <WICTextureLoader.h>
#include "Texture.h"
#include "Direct3D.h"

// コンストラクタ
Texture::Texture(wchar_t* fname)
{
	// テクスチャ作成
	DirectX::CreateWICTextureFromFile(g_pd3dDevice.Get(), fname, nullptr, &m_pTexture);
}

// デストラクタ
Texture::~Texture()
{
	// テクスチャの解放
	m_pTexture->Release();
}
