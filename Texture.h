//--------------------------------------------------------------------------------------
// File: Texture.h
//
// テクスチャクラス
//
// Date: 2015.9.2
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include <d3d11.h>

// テクスチャクラス
class Texture
{
public:
	// テクスチャハンドル
	ID3D11ShaderResourceView* m_pTexture;

	// コンストラクタ
	Texture(wchar_t* fname);
	// デストラクタ
	~Texture();
};
