#pragma once

#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetDeviceContext()

#define CLONE(type) public: virtual type* Clone() {return new type(*this);}
#define CLONE_DISABLE(type) public: virtual type* Clone() { return nullptr; assert(nullptr); }

#define SINGLE(type) private: type(); ~type(); friend class CSingleton<type>;

#define DT CTimeMgr::GetInst()->GetDeltaTime()

#define KEY_TAP(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::TAP
#define KEY_PRESSED(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::PRESSED
#define KEY_RELEASE(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::RELEASE


// Resource Type
enum class RES_TYPE
{
	MESH,
	TEXTURE,
	SHADER,
	MATERIAL,
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

enum class SHADER_STAGE
{
	VS, HS, DS, GS, PS, CS, End,
};

enum class CB_TYPE
{
	TRANSFORM,
	MATERIAL,
	ANIMATION2D,
	END,
};

enum class COMPONENT_TYPE
{
	// update
	TRANSFORM,
	CAMERA,
	ANIMATOR2D,

	// render
	MESHRENDER,

	// script
	SCRIPT,

	END,
};

enum class LEVEL_TYPE
{
	LEVEL_TYPE_TEST1,
	LEVEL_TYPE_TEST2,

	END,
};

enum class LAYER_TYPE
{
	LAYER_TEXTURE,
	LAYER_CAMERA,

	END,
};

enum class PROJ_TYPE
{
	ORTHOGRAPHIC,
	PERSPECTIVE,
};

enum class DIR_TYPE
{
	RIGHT,
	UP,
	FRONT,
};

enum class SCRIPT_TYPE
{
	CAMERAMOVE_SCRIPT,
	END,
};


enum MATERIAL_SCALAR_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,

	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,

	VEC2_0,
	VEC2_1,
	VEC2_2,
	VEC2_3,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,

	MAT_0,
	MAT_1,
	MAT_2,
	MAT_3,
};

enum MATERIAL_TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,
	TEX_6,
	TEX_7,

	TEX_END,
};