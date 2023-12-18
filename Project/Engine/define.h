#pragma once

#define SINGLE(type) private: type(); ~type(); friend class CSingleton<type>;
#define DEVICE CDevice::GetInst()->GetDevice();
#define CONTEXT CDevice::GetInst()->GetDeviceContext();

// Resource Type
enum class RES_TYPE
{
	TEXTURE,
	END,
};

enum class RS_TYPE
{
	CULL_BACK,
	CULL_FRONT,
	CULL_NONE,
	WIRE_FRAME,
	END,
};

enum class DS_TYPE
{
	LESS,
	LESS_EQUAL,
	GREATER,
	GREATER_EQUAL,
	NO_WRITE, // LESS, DepthWrite x
	NO_TEST_NO_WRITE, // Test x, DepthWrite x
	END,
};

enum class BS_TYPE
{
	DEFUALT,	// No Blending
	MASK,	// Alpha Coverage
	ALPHA_BLEND,	// Alpha °è¼ö
	ONE_ONE,	// 1 : 1 È¥ÇÕ
	END,
};