#include "pch.h"
#include "CCollisionMgr.h"

//#include "CLevel.h"
#include "CLevelMgr.h"
#include "CCollider2D.h"

CCollisionMgr::CCollisionMgr()
	: m_matrix{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::LayerCheck(UINT _left, UINT _right)
{
	UINT iRow = (UINT)_left;
	UINT iCol = (UINT)_right;

	if (iRow < iCol)
	{
		UINT iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	} // 두 개의 Layer 에 대하여 iCol 이 더 낮은 UINT 값이도록 한다.
	// iCol 에 비교적 낮은 UINT 값이 오도록 강제하는 것으로 m_matrix 의 절반에 충돌 체크 유무를 저장하고 나머지 m_matrix 공간은 사용하지 않도록 한다.

	m_matrix[iRow] |= (1 << iCol); // m_matrix 에 _Left 와 _right 간의 충돌을 계산할 것을 체크한다.
}

//void CCollisionMgr::LayerCheck(const wstring& _strLeftLayer, const wstring& _strRightLayer)
//{
//	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
//
//	
//}

void CCollisionMgr::Clear()
{
	memset(m_matrix, 0, sizeof(UINT) * (UINT)LAYER_TYPE::END);
}

void CCollisionMgr::CollisionMgrTick()
{
	CLevel* tempLevel = CLevelMgr::GetInst()->GetCurLevel();
	for (UINT iRow = 0; iRow < (UINT)LAYER_TYPE::END; ++iRow)
	{
		for (UINT iCol = 0; iCol < (UINT)LAYER_TYPE::END; ++iCol)
		{
			if (!(m_matrix[iRow] & (1 << iCol)))
			{
				continue;
			}

			// Collision check between iRow Layer and iCol Layer
			CollisionBtwLayer(tempLevel->GetLayer(iRow), tempLevel->GetLayer(iCol));
		}
	}
}

void CCollisionMgr::CollisionBtwLayer(CLayer* _leftLayer, CLayer* _rightLayer)
{
	const vector<CGameObject*>& vecLeft = _leftLayer->GetObjs();
	const vector<CGameObject*>& vecRight = _rightLayer->GetObjs();

	if (_leftLayer == _rightLayer)
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = i + 1; j < vecRight.size(); ++j)
			{
				CollisionBtwObject(vecLeft[i], vecRight[j]);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = 0; j < vecRight.size(); ++j)
			{
				CollisionBtwObject(vecLeft[i], vecRight[j]);
			}
		}
	}
}

void CCollisionMgr::CollisionBtwObject(CGameObject* _leftObject, CGameObject* _rightObject)
{
	CCollider2D* LeftObjCollider2D = _leftObject->GetComponent<CCollider2D>(COMPONENT_TYPE::COLLIDER2D);
	CCollider2D* RightObjCollider2D = _rightObject->GetComponent<CCollider2D>(COMPONENT_TYPE::COLLIDER2D);
	if (!(LeftObjCollider2D && RightObjCollider2D))
	{ // leftObject 와 rightObject 가 모두 Collider2D component 를 가지고 있으면 && 연산자에서 true 반환
		return;
	}

	// create Collision ID
	CollisionID tempID = {};
	tempID.LeftID = LeftObjCollider2D->GetID();
	tempID.RightID = RightObjCollider2D->GetID();
	// union 은 각 하나의 메모리를 변수 끼리 공유한다.
	// 즉 struct 의 값을 변경하면 메모리의 값이 변경되어 UINT_PTR 이 표현되는 값이 달라지고. 반대로
	// UINT PTR 의 값을 변경하면 메모리의 값이 변경되어 struct 로 표현되는 값이 달라진다.


	// find id
	map<UINT_PTR, bool>::iterator iter = m_mapColID.find(tempID.id);
	if (iter == m_mapColID.end())
	{
		m_mapColID.insert(make_pair(tempID.id, false));
		iter = m_mapColID.find(tempID.id);
	}

	// 두 객체 중 하나라도 이미 죽은 상태라면
	bool bDead = false;
	if (_leftObject->IsDead() || _rightObject->IsDead())
	{
		bDead = true;
	}

	// Collision Check Between Collider
	if (CollisionBtwCollider(LeftObjCollider2D, RightObjCollider2D))
	{
		// 이전 Tick 에서도 충돌 상태였다.
		if (bDead && iter->second) // 이전에 충돌 중 이었지만 객체는 현재 죽은 상태인 경우
		{
			LeftObjCollider2D->EndOverlap(RightObjCollider2D);
			RightObjCollider2D->EndOverlap(LeftObjCollider2D);
			iter->second = false;
		}
		else if (iter->second) // 이전에 충돌 중이었지만 두 객체 모두 살아있는 경우
		{
			LeftObjCollider2D->OnOverlap(RightObjCollider2D);
			RightObjCollider2D->OnOverlap(LeftObjCollider2D);
		}
		else
		{
			// 이전 프레임에서 충돌이 아니었지만 이번에 충돌하는 경우
			if(!bDead)
			{
				LeftObjCollider2D->BeginOverlap(RightObjCollider2D);
				RightObjCollider2D->BeginOverlap(LeftObjCollider2D);
				iter->second = true;
			}
		}
	}
	else // 충돌 상태가 아닌 경우
	{
		if (iter->second) // 현재 충돌 상태가 아닌데 충돌 중이라고 저장되어 있는 경우
		{
			LeftObjCollider2D->EndOverlap(RightObjCollider2D);
			RightObjCollider2D->EndOverlap(LeftObjCollider2D);
			iter->second = false;
		}
	}
}

bool CCollisionMgr::CollisionBtwCollider(CCollider2D* _leftCollider, CCollider2D* _rightCollider)
{
	// 로컬 위치
	Vec3 arrLocal[4] =
	{
		Vec3(-0.5f, 0.5f, 0.f),
		Vec3(0.5f, 0.5f, 0.f),
		Vec3(0.5f, -0.5f, 0.f),
		Vec3(-0.5f, -0.5f, 0.f),
	};

	// 두 충돌체의 두 개의 방향벡터를 구한다.
	Vec3 arrProj[4] = {};

	arrProj[0] = XMVector3TransformCoord(arrLocal[1], _leftCollider->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _leftCollider->GetColliderWorldMat());
	arrProj[1] = XMVector3TransformCoord(arrLocal[3], _leftCollider->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _leftCollider->GetColliderWorldMat());

	arrProj[2] = XMVector3TransformCoord(arrLocal[1], _rightCollider->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _rightCollider->GetColliderWorldMat());
	arrProj[3] = XMVector3TransformCoord(arrLocal[3], _rightCollider->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _rightCollider->GetColliderWorldMat());

	// 두 충돌체의 중심점 사이의 벡터
	Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _rightCollider->GetColliderWorldMat()) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _leftCollider->GetColliderWorldMat());

	// 분리축 체크
	for (int i = 0; i < 4; ++i)
	{
		Vec3 vProj = arrProj[i];
		vProj.Normalize(); // 분리축을 정규화

		float fProjDist = 0.f; // 분리축에 4개의 방향벡터가 투영된 길이들의 합
		for (int j = 0; j < 4; ++j) // ...ㄱ)
		{
			fProjDist += fabsf(arrProj[j].Dot(vProj)); // 방향벡터 arrProj[j] 가 분리축 벡터 vProj 에 투영된 거리 값 4 개를 더한다.
		}

		fProjDist /= 2.f; // 4개의 더해진 투영거리를 절반으로 나눈다.

		float fCenter = fabsf(vCenter.Dot(vProj)); // 두 충돌체의 중앙점 간의 방향 벡터를 분리축 벡터 vProj 에 투영했을 때의 거리이다.

		if (fProjDist < fCenter) // 네 개의 분리축 중에 중앙점 사이의 연결 벡터가 투영한 거리값이 분리축에 네개의 방향 벡터를 투영한 거리의 합 보다 큰 분리축이 하나라도 존재한다면 충돌하지 않았다고 판별한다.
		{
			return false;
		}
	}

	return true;;
}
