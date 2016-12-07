#pragma once

#include "MUtil.h"

typedef enum _D3DFORMAT D3DFORMAT;

namespace RealSpace2 {

struct TextureInfo
{
	u32 Width;
	u32 Height;
	u32 MipLevels;
	D3DFORMAT Format;
};

D3DPtr<struct IDirect3DTexture9> LoadTexture(const void* data, size_t size,
	float sample_ratio,
	TextureInfo& info, const char* ext = nullptr);

}