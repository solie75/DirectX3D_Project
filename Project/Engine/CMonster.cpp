#include "pch.h"
#include "CMonster.h"
#include "CTransform.h"
#include "CResMgr.h"
#include "CMeshRender.h"
#include "CState.h"
#include "CCollider2D.h"

CMonster::CMonster()
	: CGameObject()
	, m_directionType(DIRECTION_TYPE::DOWN)
{
	this->ObjInit();
}

CMonster::~CMonster()
{
}

void CMonster::ObjInit()
{
	SetName(L"Monster");

	// Transform
	CTransform* tempTF = new CTransform;
	tempTF->SetWorldPos(Vec3(200.f, 0.f, 0.f));
	tempTF->SetWorldScale(Vec3(100.f, 100.f, 1.f));
	AddComponent(tempTF);

	// MeshRender
	CMeshRender* tempMR = new CMeshRender;
	tempMR->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DefaultMtrl2"));
	tempMR->GetMaterial()->GetShader()->SetDomain(DOMAIN_TYPE::DOMAIN_MASK);
	tempMR->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	AddComponent(tempMR);

	// State
	AddComponent(new CState((UINT)OBJECT_STATE::IDLE, DIRECTION_TYPE::DOWN));

	// CCollider2D
	CCollider2D* tempCD = new CCollider2D;
	// 절대적인 위치나 크기가 아니라 캐릭터에 대해 비례적으로 적용된다.
	tempCD->SetOffsetPos(Vec2(0.f, 0.f));
	tempCD->SetOffsetScale(Vec2(1.f, 1.f));
	AddComponent(tempCD);
}

void CMonster::ObjTick()
{
	CGameObject::ObjTick();
}

void CMonster::ObjFinaltick()
{
	CGameObject::ObjFinaltick();
}

void CMonster::ObjRender()
{
	CGameObject::ObjRender();
}
