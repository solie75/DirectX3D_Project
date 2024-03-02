#include "pch.h"
#include "CCamera.h"
#include "CTransform.h"
#include "CDevice.h"
#include "CKeyMgr.h"
//#include "CLevel.h"
#include "CLevelMgr.h"
#include "CRenderComponent.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_ProjType(PROJ_TYPE::PERSPECTIVE)
	, m_fScale(1.f)
	, m_fAspectRatio(1.f)
	, m_iLayerMask(0)
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
	, m_iLayerMask(_other.m_iLayerMask)
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

	render_opaque();
	render_mask();
	render_transparent();
	render_ui();
}

void CCamera::CompInit()
{
}

void CCamera::CompTick()
{
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

	matRotForView._11 = vRUF[0].x;	matRotForView._12 = vRUF[1].x;	matRotForView._13 = vRUF[2].x;
	matRotForView._21 = vRUF[0].y;	matRotForView._22 = vRUF[1].y;	matRotForView._23 = vRUF[2].y;
	matRotForView._31 = vRUF[0].z;	matRotForView._32 = vRUF[1].z;	matRotForView._33 = vRUF[2].z;

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

void CCamera::SortObject()
{
	// 이전 프레임의 분류된 정보 삭제
	ClearObject();

	CLevel* tempCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		if (m_iLayerMask & (1 << i))
		{
			CLayer* tempLayer = tempCurLevel->GetLayer(i);
			const vector<CGameObject*>& vecTempObject = tempLayer->GetObjs();

			for (size_t j = 0; j < vecTempObject.size(); ++j)
			{
				CRenderComponent* tempRenderComp = vecTempObject[j]->GetRenderComponent();

				// exclude Object without RenderingComp
				if (nullptr == tempRenderComp
					|| nullptr == tempRenderComp->GetMaterial()
					|| nullptr == tempRenderComp->GetMaterial()->GetShader())
				{
					continue;
				}

				// sort by domain type
				DOMAIN_TYPE eDomain = tempRenderComp->GetMaterial()->GetShader()->GetDomainType();
				switch(eDomain)
				{
				case DOMAIN_TYPE::DOMAIN_OPAQUE:
					m_vecOpaque.push_back(vecTempObject[j]);
					break;
				case DOMAIN_TYPE::DOMAIN_MASK:
					m_vecMask.push_back(vecTempObject[j]);
					break;
				case DOMAIN_TYPE::DOMAIN_TRANSPARENT:
					m_vecTransparent.push_back(vecTempObject[j]);
					break;
				case DOMAIN_TYPE::DOMAIN_UI:
					m_vecUI.push_back(vecTempObject[j]);
					break;
				}
			}
		}
	}
}

void CCamera::ClearObject()
{
	m_vecOpaque.clear();
	m_vecMask.clear();
	m_vecTransparent.clear();
	m_vecUI.clear();
}

void CCamera::SetLayerMask(int _iLayer, bool _visible)
{
	if (_visible)
	{
		m_iLayerMask |= 1 << _iLayer;
	}
	else
	{
		m_iLayerMask &= ~(1 << _iLayer);
	}
}

void CCamera::SetLayerMaskAll(bool _visible)
{
	if (_visible)
	{
		m_iLayerMask = 0xffffffff;
	}
	else
	{
		m_iLayerMask = 0;
	}
}

void CCamera::SetCameraType(CAMERA_TYPE _type)
{
	m_CamType = _type;
}

void CCamera::render_opaque()
{
	for (int i = 0; i < m_vecOpaque.size(); ++i)
	{
		m_vecOpaque[i]->ObjRender();
	}
}

void CCamera::render_mask()
{
	for (int i = 0; i < m_vecMask.size(); ++i)
	{
		m_vecMask[i]->ObjRender();
	}
}

void CCamera::render_transparent()
{
	for (int i = 0; i < m_vecTransparent.size(); ++i)
	{
		m_vecTransparent[i]->ObjRender();
	}
}

void CCamera::render_ui()
{
	for (int i = 0; i < m_vecUI.size(); ++i)
	{
		m_vecUI[i]->ObjRender();
	}
}
