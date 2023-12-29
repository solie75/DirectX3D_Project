#pragma once



#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetDeviceContext()

#define CLONE(type) public: virtual type* Clone() {return new type(*this);}
#define CLONE_DISABLE(type) public: virtual type* Clone() { return nullptr; assert(nullptr); }

#define SINGLE(type) private: type(); ~type(); friend class CSingleton<type>;

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
	ALPHA_BLEND,	// Alpha ���
	ONE_ONE,	// 1 : 1 ȥ��
	END,
};

enum class SHADER_STAGE
{
	VS, HS, DS, GS, PS, CS, End,
};

enum class CB_TYPE
{
	TRANSFORM,
	END,
};