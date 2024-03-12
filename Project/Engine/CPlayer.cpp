#include "pch.h"
#include "CPlayer.h"
#include "CTransform.h"
#include "CAnimator2D.h"
#include "CMeshRender.h"
#include "CResMgr.h"
#include "CPlayerScript.h"
#include "CState.h"
#include "CCollider2D.h"

CPlayer::CPlayer()
	: CGameObject()
	, m_directionType(DIRECTION_TYPE::DOWN)
{
	this->ObjInit();
}

CPlayer::~CPlayer()
{
}

void CPlayer::ObjInit()
{
	SetName(L"Player");

	// Add Component

	// Transform
	CTransform* tempTF = new CTransform;
	tempTF->SetWorldPos(Vec3(0.f, 0.f, 0.f));
	tempTF->SetWorldScale(Vec3(100.f, 100.f, 1.f));
	AddComponent(tempTF);

	// MeshRender
	CMeshRender* tempMR = new CMeshRender;
	tempMR->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Ain2DMtrl"));
	tempMR->GetMaterial()->GetShader()->SetDomain(DOMAIN_TYPE::DOMAIN_MASK);
	tempMR->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	AddComponent(tempMR);

	// PlayScript
	AddComponent(new CPlayerScript);

	// Animator
	CAnimator2D* tempANI = new CAnimator2D;
	tAtlasData tempAtData;
	tempANI->CreateAni2D(L"Will_Idle_Down", tempAtData);
	tempANI->CreateAni2D(L"Will_Idle_Right", tempAtData);
	tempANI->CreateAni2D(L"Will_Idle_Left", tempAtData);
	tempANI->CreateAni2D(L"Will_Idle_Up", tempAtData);
	tempANI->CreateAni2D(L"Will_Walk_Right", tempAtData);
	tempANI->CreateAni2D(L"Will_Walk_Left", tempAtData);
	tempANI->CreateAni2D(L"Will_Walk_Up", tempAtData);
	tempANI->CreateAni2D(L"Will_Walk_Down", tempAtData);
	AddComponent(tempANI);

	tempANI->PlayAni2D(L"Will_Idle_Down", true);

	// State
	AddComponent(new CState((UINT)OBJECT_STATE::IDLE, DIRECTION_TYPE::DOWN));

	// CCollider2D
	CCollider2D* tempCD = new CCollider2D;
	// 절대적인 위치나 크기가 아니라 캐릭터에 대해 비례적으로 적용된다.
	tempCD->SetOffsetPos(Vec2(1.f, 1.f));
	tempCD->SetOffsetScale(Vec2(0.5f, 0.5f));
	AddComponent(tempCD);
}

void CPlayer::ObjTick()
{
	CGameObject::ObjTick();
}

void CPlayer::ObjFinaltick()
{
	CGameObject::ObjFinaltick();
}

void CPlayer::ObjRender()
{
	CGameObject::ObjRender();
}
