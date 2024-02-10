#include "pch.h"
#include "CCameraMoveScript.h"
#include "CTransform.h"
#include "CKeyMgr.h"

CCameraMoveScript::CCameraMoveScript()
	: CScript(SCRIPT_TYPE::CAMERAMOVE_SCRIPT)
	, m_fCamSpeed(0.2f)
{
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::ScriptTick()
{
	CTransform* tempTransform = GetOtherComp<CTransform>(COMPONENT_TYPE::TRANSFORM);
	Vec3 tempPos = tempTransform->GetWorldPos();


	if (KEY_PRESSED(KEY::LEFT))
	{
		tempPos.x -= 0.2f;
	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		tempPos.x += 0.2f;
	}
	if (KEY_PRESSED(KEY::UP))
	{
		tempPos.y += 0.2f;
	}
	if (KEY_PRESSED(KEY::DOWN))
	{
		tempPos.y -= 0.2f;
	}
	if (KEY_PRESSED(KEY::Q))
	{
		tempPos.z += 0.2f;
	}
	if (KEY_PRESSED(KEY::W))
	{
		tempPos.z -= 0.2f;
	}

	tempTransform->SetWorldPos(tempPos);
}
