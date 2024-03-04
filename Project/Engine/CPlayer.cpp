#include "pch.h"
#include "CPlayer.h"
#include "CTransform.h"
#include "CAnimator2D.h"
#include "CMeshRender.h"
#include "CResMgr.h"
#include "CPlayerScript.h"

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
	CTransform* tempTF = new CTransform;
	tempTF->SetWorldPos(Vec3(0.f, 0.f, 0.f));
	tempTF->SetWorldScale(Vec3(100.f, 100.f, 1.f));
	AddComponent(tempTF);

	CMeshRender* tempMR = new CMeshRender;
	tempMR->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Ain2DMtrl"));
	tempMR->GetMaterial()->GetShader()->SetDomain(DOMAIN_TYPE::DOMAIN_MASK);
	tempMR->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	AddComponent(tempMR);

	AddComponent(new CPlayerScript);

	CAnimator2D* tempANI = new CAnimator2D;
	tAtlasData tempAtData;
	tempANI->CreateAni2D(L"Will_Idle_Down", tempAtData);
	AddComponent(tempANI);

	tempANI->PlayAni2D(L"Will_Idle_Down", true);
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
