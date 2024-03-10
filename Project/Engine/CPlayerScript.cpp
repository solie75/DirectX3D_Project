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

	CTransform* tempTransform = GetOtherComp<CTransform>(COMPONENT_TYPE::TRANSFORM);
	Vec3 WorldPos = tempTransform->GetWorldPos();

	Vec2 tempPos = Vec2(0.f);
	// PRESSED
	if (KEY_PRESSED(KEY::A))
	{
		if (tempState->GetCurDirectionType() != DIRECTION_TYPE::RIGHT)
		{
			tempPos.x -= 0.1f;
		}
	}
	if (KEY_PRESSED(KEY::D))
	{
		if (tempState->GetCurDirectionType() != DIRECTION_TYPE::LEFT)
		{
			tempPos.x += 0.1f;
		}
	}
	if (KEY_PRESSED(KEY::W))
	{
		if (tempState->GetCurDirectionType() != DIRECTION_TYPE::DOWN)
		{
			tempPos.y += 0.1f;
		}
	}
	if (KEY_PRESSED(KEY::S))
	{
		if (tempState->GetCurDirectionType() != DIRECTION_TYPE::UP)
		{
			tempPos.y -= 0.1f;
		}
	}

	if (m_vecDir.size() > 1)
	{
		// 대각 선으로 이동할 때의 속도 조절
		tempPos *= Vec2(0.7f);
	}

	WorldPos.x += tempPos.x;
	WorldPos.y += tempPos.y;

	tempTransform->SetWorldPos(WorldPos);

	// TAP
	if (KEY_TAP(KEY::A))
	{
			tempAni2D->PlayAni2D(L"Will_Walk_Left", true);
			tempState->SetCurState((UINT)OBJECT_STATE::WALK, DIRECTION_TYPE::LEFT);
			m_vecDir.push_back(DIRECTION_TYPE::LEFT);
	}
	if (KEY_TAP(KEY::D))
	{
			tempAni2D->PlayAni2D(L"Will_Walk_Right", true);
			tempState->SetCurState((UINT)OBJECT_STATE::WALK, DIRECTION_TYPE::RIGHT);
			m_vecDir.push_back(DIRECTION_TYPE::RIGHT);
	}
	if (KEY_TAP(KEY::W))
	{
			tempAni2D->PlayAni2D(L"Will_Walk_Up", true);
			tempState->SetCurState((UINT)OBJECT_STATE::WALK, DIRECTION_TYPE::UP);
			m_vecDir.push_back(DIRECTION_TYPE::UP);
	}
	if (KEY_TAP(KEY::S))
	{
			tempAni2D->PlayAni2D(L"Will_Walk_Down", true);
			tempState->SetCurState((UINT)OBJECT_STATE::WALK, DIRECTION_TYPE::DOWN);
			m_vecDir.push_back(DIRECTION_TYPE::DOWN);
	}

	// RELEASE
	if (KEY_RELEASE(KEY::A))
	{
		if (m_vecDir.size() > 1 )
		{
			EraseDir(DIRECTION_TYPE::LEFT);
			if (tempState->GetCurDirectionType() == DIRECTION_TYPE::LEFT)
			{
				PlayWalkAniWithPrevDir(DIRECTION_TYPE::LEFT);
			}
		}
		else if(m_vecDir.size() == 1)
		{
			m_vecDir.clear();
			tempAni2D->PlayAni2D(L"Will_Idle_Left", true);
			tempState->SetCurState((UINT)OBJECT_STATE::IDLE);
		}
	}
	if (KEY_RELEASE(KEY::D))
	{
		if (m_vecDir.size() > 1)
		{
			EraseDir(DIRECTION_TYPE::RIGHT);
			if (tempState->GetCurDirectionType() == DIRECTION_TYPE::RIGHT)
			{
				PlayWalkAniWithPrevDir(DIRECTION_TYPE::RIGHT);
			}
		}
		else  if (m_vecDir.size() == 1)
		{
			m_vecDir.clear();
			tempAni2D->PlayAni2D(L"Will_Idle_Right", true);
			tempState->SetCurState((UINT)OBJECT_STATE::IDLE);
		}
	}
	if (KEY_RELEASE(KEY::W))
	{
		if (m_vecDir.size() > 1)
		{
			EraseDir(DIRECTION_TYPE::UP);
			if (tempState->GetCurDirectionType() == DIRECTION_TYPE::UP)
			{
				PlayWalkAniWithPrevDir(DIRECTION_TYPE::UP);
			}
		}
		else if (m_vecDir.size() == 1)
		{
			m_vecDir.clear();
			tempAni2D->PlayAni2D(L"Will_Idle_Up", true);
			tempState->SetCurState((UINT)OBJECT_STATE::IDLE);
		}
	}
	if (KEY_RELEASE(KEY::S))
	{
		if (m_vecDir.size() > 1)
		{
			EraseDir(DIRECTION_TYPE::DOWN);
			if (tempState->GetCurDirectionType() == DIRECTION_TYPE::DOWN)
			{
				PlayWalkAniWithPrevDir(DIRECTION_TYPE::DOWN);
			}
		}
		else if (m_vecDir.size() == 1)
		{
			m_vecDir.clear();
			tempAni2D->PlayAni2D(L"Will_Idle_Down", true);
			tempState->SetCurState((UINT)OBJECT_STATE::IDLE);
		}
	}
}

void CPlayerScript::ScriptFinalTick()
{
}

void CPlayerScript::PlayWalkAniWithPrevDir(DIRECTION_TYPE _type)
{
	CAnimator2D* tempAni2D = GetOwnerObj()->GetComponent<CAnimator2D>(COMPONENT_TYPE::ANIMATOR2D);
	CState* tempState = GetOwnerObj()->GetComponent<CState>(COMPONENT_TYPE::STATE);
	std::vector<DIRECTION_TYPE>::iterator iter = m_vecDir.end();
	iter--; // m_vecDir 의 맨 마지막 요소를 가리킨다.

	switch (*iter)
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

void CPlayerScript::EraseDir(DIRECTION_TYPE _type)
{
	vector<DIRECTION_TYPE>::iterator iter = m_vecDir.begin();
	for (; iter != m_vecDir.end(); iter++)
	{
		if (*iter == _type)
		{
			m_vecDir.erase(iter);
			return;
		}
	}
}
