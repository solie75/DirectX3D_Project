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

	GRAPHICS_SHADER,
	COMPUTE_SHADER,

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
	DEFAULT,	// No Blending
	MASK,	// Alpha Coverage
	ALPHA_BLEND,	// Alpha 계수
	ONE_ONE,	// 1 : 1 혼합
	END,
};

enum class DOMAIN_TYPE
{
	DOMAIN_DEFERRED,		// 지연 렌더링 오브젝트
	DOMAIN_DEFERRED_DECAL,	// Deferred Decal(광원 적용 가능한 Decal)

	DOMAIN_OPAQUE,			// 불투명 오브젝트
	DOMAIN_MASK,			// 불투명, 완전 투명
	DOMAIN_DECAL,			// 데칼 오브젝트
	DOMAIN_TRANSPARENT,		// 반투명
	DOMAIN_POSTPROCESS,		// 후 처리
	DOMAIN_UI,

	DOMAIN_LIGHT,			// 광원 타입 
	DOMAIN_UNDEFINED,		// 미정
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
	GLOBAL,
	END,
};

enum class COMPONENT_TYPE
{
	// update
	TRANSFORM,
	CAMERA,
	ANIMATOR2D,
	STATE,
	COLLIDER2D,

	// render
	MESHRENDER,
	PARTICLESYSTEM,

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
	LAYER_PLAYER,
	LAYER_MONSTER,
	LAYER_CAMERA,
	LAYER_UI,
	LAYER_EDITOR,
	LAYER_TEST,
	END,
};

enum class COLLIDER_TYPE
{
	PLAYER,
	MONSTER,
	PLAYER_PROJECTILE,
	MONSTER_PROJECTILE,
	BACKGROUND,
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
	PLAYER_SCRIPT,
	CAMERAMOVE_SCRIPT,
	END,
};

enum class CAMERA_TYPE
{
	MAIN,
	UI,
	EDITOR,
	END,
};

enum class DIRECTION_TYPE
{
	RIGHT,
	DOWN,
	LEFT,
	UP,
	END,
};

enum class OBJECT_STATE
{
	IDLE,
	WALK,
	ATTACK,
	HIT,
	ROLL,
	END,
};

enum class SHAPE_TYPE
{
	RECT,
	CIRCLE,
	CUBE,
	SPHERE,
	END,
};

enum class SB_TYPE
{
	READ_ONLY,
	READ_WRITE,
};

enum class PARTICLE_MODULE
{
	PARTICLE_SPAWN,
	COLOR_CHANGE,
	SCALE_CHANGE,
	ADD_VELOCITY,

	DRAG,
	NOISE_FORCE,
	RENDER,
	DUMMY_3,

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

enum PIPELINE_STAGE
{
	PS_VERTEX = 0x01,
	PS_HULL = 0x02,
	PS_DOMAIN = 0x04,
	PS_GEOMETRY = 0x08,
	PS_PIXEL = 0x10,

	PS_ALL = PS_VERTEX | PS_HULL | PS_DOMAIN | PS_GEOMETRY | PS_PIXEL,
};

