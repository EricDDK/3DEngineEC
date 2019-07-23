#ifndef _TEST_TEXTURE_H__
#define _TEST_TEXTURE_H__

#include "TestCommon.h"
#include "Common/3DEngine.h"
#include "Engine/Texture.h"

class TestTexture
{
public:
	void testTexture()
	{
		engine::Texture tex;
		tex.load("ImageFile.png");
		tex.setActive();
		tex.unload();
	}
};

#endif