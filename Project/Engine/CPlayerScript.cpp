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
	int iPressedCount = 0;

	CAnimator2D* tempAni2D = GetOwnerObj()->GetComponent<CAnimator2D>(COMPONENT_TYPE::ANIMATOR2D);
	CState* tempState = GetOwnerObj()->GetComponent<CState>(COMPONENT_TYPE::STATE);

	
	CTransform* tempTransform = GetOtherComp<CTransform>(COMPONENT_TYPE::TRANSFORM);
	Vec3 WorldPos = tempTransform->GetWorldPos();

	Vec2 tempPos = Vec2(0.f);
	// PRESSED
	if (KEY_PRESSED(KEY::A))
	{
		if (tempState->GetCurDirectionType() != DIRECTION_TYPE::RIGHT)
		{
			iPressedCount++;
			tempPos.x -= 0.1f;
		}
	}
	if (KEY_PRESSED(KEY::D))
	{
		if (tempState->GetCurDirectionType() != DIRECTION_TYPE::LEFT)
		{
			iPressedCount++;
			tempPos.x += 0.1f;
		}
	}
	if (KEY_PRESSED(KEY::W))
	{
		if (tempState->GetCurDirectionType() != DIRECTION_TYPE::DOWN)
		{
			iPressedCount++;
			tempPos.y += 0.1f;
		}
	}
	if (KEY_PRESSED(KEY::S))
	{
		if (tempState->GetCurDirectionType() != DIRECTION_TYPE::UP)
		{
			iPressedCount++;
			tempPos.y -= 0.1f;
		}
	}

	if (iPressedCount > 1)
	{
		// 대각 선으로 이동할 때의 속도 조절
		tempPos *= Vec2(0.7f);
	}

	WorldPos.x += tempPos.x;
	WorldPos.y += tempPos.y;

	// TAP
	if (KEY_TAP(KEY::A))
	{
		if (iPressedCount < 3)
		{
			tempAni2D->PlayAni2D(L"Will_Walk_Left", true);
			tempState->SetCurState((UINT)OBJECT_STATE::WALK, DIRECTION_TYPE::LEFT);
		}
	}
	if (KEY_TAP(KEY::D))
	{
		if (iPressedCount < 3)
		{
			tempAni2D->PlayAni2D(L"Will_Walk_Right", true);
			tempState->SetCurState((UINT)OBJECT_STATE::WALK, DIRECTION_TYPE::RIGHT);
		}
	}
	if (KEY_TAP(KEY::W))
	{
		if (iPressedCount < 3)
		{
			tempAni2D->PlayAni2D(L"Will_Walk_Up", true);
			tempState->SetCurState((UINT)OBJECT_STATE::WALK, DIRECTION_TYPE::UP);
		}
	}
	if (KEY_TAP(KEY::S))
	{
		if (iPressedCount < 3)
		{
			tempAni2D->PlayAni2D(L"Will_Walk_Down", true);
			tempState->SetCurState((UINT)OBJECT_STATE::WALK, DIRECTION_TYPE::DOWN);
		}
	}

	// RELEASE
	if (KEY_RELEASE(KEY::A) && tempState->GetCurDirectionType() == DIRECTION_TYPE::LEFT)
	{
		if (iPressedCount >= 1)
		{
			PlayWalkAniWithPrevDir();
		}
		else
		{
			tempAni2D->PlayAni2D(L"Will_Idle_Left", true);
			tempState->SetCurState((UINT)OBJECT_STATE::IDLE);
		}
	}
	if (KEY_RELEASE(KEY::D) && tempState->GetCurDirectionType() == DIRECTION_TYPE::RIGHT)
	{
		if (iPressedCount >= 1)
		{
			PlayWalkAniWithPrevDir();
		}
		else
		{
			tempAni2D->PlayAni2D(L"Will_Idle_Right", true);
			tempState->SetCurState((UINT)OBJECT_STATE::IDLE);
		}
	}
	if (KEY_RELEASE(KEY::W) && tempState->GetCurDirectionType() == DIRECTION_TYPE::UP)
	{
		if (iPressedCount >= 1)
		{
			PlayWalkAniWithPrevDir();
		}
		else
		{
			tempAni2D->PlayAni2D(L"Will_Idle_Up", true);
			tempState->SetCurState((UINT)OBJECT_STATE::IDLE);
		}
	}
	if (KEY_RELEASE(KEY::S) && tempState->GetCurDirectionType() == DIRECTION_TYPE::DOWN)
	{
		if (iPressedCount >= 1)
		{
			PlayWalkAniWithPrevDir();
		}
		else
		{
			tempAni2D->PlayAni2D(L"Will_Idle_Down", true);
			tempState->SetCurState((UINT)OBJECT_STATE::IDLE);
		}
	}

	tempTransform->SetWorldPos(WorldPos);
}

void CPlayerScript::ScriptFinalTick()
{
}

void CPlayerScript::PlayWalkAniWithPrevDir()
{
	CAnimator2D* tempAni2D = GetOwnerObj()->GetComponent<CAnimator2D>(COMPONENT_TYPE::ANIMATOR2D);
	CState* tempState = GetOwnerObj()->GetComponent<CState>(COMPONENT_TYPE::STATE);

	switch (tempState->GetPrevDirectionType())
	{
	case DIRECTION_TYPE::RIGHT :
		tempAni2D->PlayAni2D(L"Will_Walk_Right", true);
		tempState->SetDirectionType(DIRECTION_TYPE::RIGHT);
		break;
	case DIRECTION_TYPE::LEFT:
		tempAni2D->PlayAni2D(L"Will_Walk_Left", true);
		tempState->SetDirectionType(DIRECTION_TYPE::LEFT);
		break;
	case DIRECTION_TYPE::DOWN:
		tempAni2D->PlayAni2D(L"Will_Walk_Down", true);
		tempState->SetDirectionType(DIRECTION_TYPE::DOWN);
		break;
	case DIRECTION_TYPE::UP:
		tempAni2D->PlayAni2D(L"Will_Walk_Up", true);
		tempState->SetDirectionType(DIRECTION_TYPE::UP);
		break;
	}
}