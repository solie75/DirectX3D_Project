#include "pch.h"
#include "CPlayerScript.h"
#include "CKeyMgr.h"
#include "CTransform.h"

CPlayerScript::CPlayerScript()
	: CScript(SCRIPT_TYPE::PLAYER_SCRIPT)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::ScriptInit()
{
}

void CPlayerScript::ScriptTick()
{
	CTransform* tempTransform = GetOtherComp<CTransform>(COMPONENT_TYPE::TRANSFORM);
	Vec3 tempPos = tempTransform->GetWorldPos();


	if (KEY_PRESSED(KEY::A))
	{
		tempPos.x -= 0.2f;
	}
	if (KEY_PRESSED(KEY::D))
	{
		tempPos.x += 0.2f;
	}
	if (KEY_PRESSED(KEY::W))
	{
		tempPos.y += 0.2f;
	}
	if (KEY_PRESSED(KEY::S))
	{
		tempPos.y -= 0.2f;
	}
	/*if (KEY_PRESSED(KEY::Q))
	{
		tempPos.z += 0.2f;
	}
	if (KEY_PRESSED(KEY::W))
	{
		tempPos.z -= 0.2f;
	}*/

	tempTransform->SetWorldPos(tempPos);
}

void CPlayerScript::ScriptFinalTick()
{
}
