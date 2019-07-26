#ifndef _TEST_TEXTURE_H__
#define _TEST_TEXTURE_H__

#include "TestCommon.h"
#include "Common/3DEngine.h"
#include "Render/Texture.h"

class TestTexture
{
public:
	void testTexture()
	{
		engine::Texture tex;
		//  can't test it. it will refuse the GL layer.
		/*auto loadSuccess = tex.load("ImageFile.png");
		EXPECT(loadSuccess, true);
		tex.setActive();
		tex.unload();*/
	}
};

#endif