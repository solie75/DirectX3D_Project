#include "pch.h"
#include "CPlayerScript.h"
#include "CKeyMgr.h"
#include "CTransform.h"
#include "CAnimator2D.h"
#include "CState.h"

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
	CAnimator2D* tempAni2D = GetOwnerObj()->GetComponent<CAnimator2D>(COMPONENT_TYPE::ANIMATOR2D);
	CState* tempState = GetOwnerObj()->GetComponent<CState>(COMPONENT_TYPE::STATE);
	// Change Animatino And State Idle -> Walk
	if (KEY_TAP(KEY::A))
	{
		tempAni2D->PlayAni2D(L"Will_Walk_Left", true);
		tempState->SetCurState((UINT)PLAYER_STATE::)
	}
	else if (KEY_TAP(KEY::D))
	{
		tempAni2D->PlayAni2D(L"Will_Walk_Right", true);
	}
	else if (KEY_TAP(KEY::W))
	{
		tempAni2D->PlayAni2D(L"Will_Walk_Up", true);
	}
	else if (KEY_TAP(KEY::S))
	{
		tempAni2D->PlayAni2D(L"Will_Walk_Down", true);
	}

	// Change Animation and State Walk -> Idle
	if (KEY_RELEASE(KEY::A))
	{
		tempAni2D->PlayAni2D(L"Will_Idle_Left", true);
	}
	else if (KEY_RELEASE(KEY::D))
	{
		tempAni2D->PlayAni2D(L"Will_Idle_Right", true);
	}
	else if (KEY_RELEASE(KEY::W))
	{
		tempAni2D->PlayAni2D(L"Will_Idle_Up", true);
	}
	else if (KEY_RELEASE(KEY::S))
	{
		tempAni2D->PlayAni2D(L"Will_Walk_Down", true);
	}

	CTransform* tempTransform = GetOtherComp<CTransform>(COMPONENT_TYPE::TRANSFORM);
	Vec3 tempPos = tempTransform->GetWorldPos();

	// Change Transform
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

	tempTransform->SetWorldPos(tempPos);
}

void CPlayerScript::ScriptFinalTick()
{
}
