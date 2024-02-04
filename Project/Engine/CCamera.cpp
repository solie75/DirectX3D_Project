#include "pch.h"
#include "CCamera.h"
#include "CTransform.h"
#include "CDevice.h"
#include "CKeyMgr.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_ProjType(PROJ_TYPE::ORTHOGRAPHIC)
	, m_fScale(1.f)
	, m_fAspectRatio(1.f)
{
	SetName(L"Camera");

	Vec2 vRenderResol = CDevice::GetInst()->GetRTResolution();
	m_fAspectRatio = vRenderResol.x / vRenderResol.y;
}

CCamera::CCamera(const CCamera& _other)
	: CComponent(_other)
	, m_ProjType(_other.m_ProjType)
	, m_fScale(_other.m_fScale)
	, m_fAspectRatio(_other.m_fAspectRatio)
{
}

CCamera::~CCamera()
{
}

void CCamera::CameraRender()
{
	// Matrix Update
	g_transform.matView = m_matView;
	g_transform.matProj = m_matProj;
}

void CCamera::CompInit()
{
}

void CCamera::CompTick()
{
	CTransform* tempTransform = GetOtherComp<CTransform>(COMPONENT_TYPE::TRANSFORM);
	Vec3 tempPos = tempTransform->GetWorldPos();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::TAP)
	{
		tempPos.x -= 0.2f;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::TAP)
	{
		tempPos.x += 0.2f;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::TAP)
	{
		tempPos.y += 0.2f;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::TAP)
	{
		tempPos.y -= 0.2f;
	}

	tempTransform->SetWorldPos(tempPos);
}

void CCamera::CompFinalTick()
{
	CalViewMat();

	CalProjMat();
}

void CCamera::CalViewMat()
{
	// =======================
	// View Matrix Calculation
	// =======================
	m_matView = XMMatrixIdentity();

	// 카메라를 원점으로 이동 시키는 Matrix
	Vec3 vCamPos = GetOtherComp<CTransform>(COMPONENT_TYPE::TRANSFORM)->GetWorldPos();
	Matrix matTransForView = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);

	// 카메라의 시점 방향을 z 축과 평행하게 만드는 회전 행렬
	Matrix matRotForView = XMMatrixIdentity();

	
	Vec3 vRUF[3] = {};
	for (int i = 0; i < 3; ++i)
	{
		vRUF[i] = GetOtherComp<CTransform>(COMPONENT_TYPE::TRANSFORM)->GetWorldDir((DIR_TYPE)i);
	}

	matRotForView._11 = vRUF->x;	matRotForView._12 = vRUF->x;	matRotForView._13 = vRUF->x;
	matRotForView._21 = vRUF->y;	matRotForView._22 = vRUF->y;	matRotForView._23 = vRUF->y;
	matRotForView._31 = vRUF->z;	matRotForView._32 = vRUF->z;	matRotForView._33 = vRUF->z;

	m_matView = matTransForView * matRotForView;
}

void CCamera::CalProjMat()
{
	// =============================
	// Projection Matrix Calculation
	// =============================

	m_matProj = XMMatrixIdentity();
	if (PROJ_TYPE::ORTHOGRAPHIC == m_ProjType)
	{
		Vec2 vResolution = CDevice::GetInst()->GetRTResolution(); // GetRTResolution 추가
		m_matProj = XMMatrixOrthographicLH(vResolution.x * (1.f / m_fScale), vResolution.y * (1.f / m_fScale), 1.f, 10000.f);
	}
	else
	{
		m_matProj = XMMatrixPerspectiveFovLH(XM_PI / 2.f, m_fAspectRatio, 1.f, 10000.f);
	}
}
