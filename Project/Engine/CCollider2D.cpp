#include "pch.h"
#include "CCollider2D.h"
#include "CTransform.h"

CCollider2D::CCollider2D()
	: CComponent(COMPONENT_TYPE::COLLIDER2D)
	, m_bVisible(true)
{
}

CCollider2D::~CCollider2D()
{
}

void CCollider2D::CompFinalTick()
{
	if (m_bVisible == true)
	{
		assert(0 <= m_iCollisionCount);

		m_matWorldCollider2D = XMMatrixScaling(m_vOffsetScale.x, m_vOffsetScale.y, m_vOffsetScale.z);
		m_matWorldCollider2D *= XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, m_vOffsetPos.z);

		const Matrix& matWorld = GetOwnerObj()->GetComponent<CTransform>(COMPONENT_TYPE::TRANSFORM)->GetWorldMat();

		m_matWorldCollider2D =  m_matWorldCollider2D* matWorld; // 여기에서 반대로 matWorld * m_matWorldCollider2D 가 되면 움직임의 중심이 게임 객체가 아니라 월드 맵 상의 중심이 된다.
		


		// Set Debug Obj Color
		Vec4 vColor = Vec4(0.f, 1.f, 0.f, 1.f);
		if (0 < m_iCollisionCount)
		{
			vColor = Vec4(1.f, 0.f, 0.f, 1.f);
		}

		// Add Debug Shape info
		if (SHAPE_TYPE::RECT == m_ShapeType)
		{
			SetDebugRect(m_matWorldCollider2D, vColor, 0.f);
		}
		else// SHAPE_TYPE::CIRCLE == m_ShapeType
		{
			SetDebugCircle(m_matWorldCollider2D, vColor, 0.f);
		}
	}
}

void CCollider2D::SetOffsetPos(Vec2 _vOffsetPos)
{
	m_vOffsetPos = Vec3(_vOffsetPos.x, _vOffsetPos.y, 0.f);
}

void CCollider2D::SetOffsetScale(Vec2 _vOffsetScale)
{
	m_vOffsetScale = Vec3(_vOffsetScale.x, _vOffsetScale.y, 1.f);
}

//void CCollider2D::SetBoolAbsolute(bool _v)
//{
//	m_bAbsolute = _v;
//}

void CCollider2D::SetColider2DType(SHAPE_TYPE _type)
{
	m_ShapeType = _type;
}

void CCollider2D::BeginOverlap(CCollider2D* _other)
{
	m_iCollisionCount++;
}

void CCollider2D::OnOverlap(CCollider2D* _other)
{

}

void CCollider2D::EndOverlap(CCollider2D* _other)
{
	m_iCollisionCount--;
}
