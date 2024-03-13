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
	} // �� ���� Layer �� ���Ͽ� iCol �� �� ���� UINT ���̵��� �Ѵ�.
	// iCol �� ���� ���� UINT ���� ������ �����ϴ� ������ m_matrix �� ���ݿ� �浹 üũ ������ �����ϰ� ������ m_matrix ������ ������� �ʵ��� �Ѵ�.

	m_matrix[iRow] |= (1 << iCol); // m_matrix �� _Left �� _right ���� �浹�� ����� ���� üũ�Ѵ�.
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
	{ // leftObject �� rightObject �� ��� Collider2D component �� ������ ������ && �����ڿ��� true ��ȯ
		return;
	}

	// create Collision ID
	CollisionID tempID = {};
	tempID.LeftID = LeftObjCollider2D->GetID();
	tempID.RightID = RightObjCollider2D->GetID();
	// union �� �� �ϳ��� �޸𸮸� ���� ���� �����Ѵ�.
	// �� struct �� ���� �����ϸ� �޸��� ���� ����Ǿ� UINT_PTR �� ǥ���Ǵ� ���� �޶�����. �ݴ��
	// UINT PTR �� ���� �����ϸ� �޸��� ���� ����Ǿ� struct �� ǥ���Ǵ� ���� �޶�����.


	// find id
	map<UINT_PTR, bool>::iterator iter = m_mapColID.find(tempID.id);
	if (iter == m_mapColID.end())
	{
		m_mapColID.insert(make_pair(tempID.id, false));
		iter = m_mapColID.find(tempID.id);
	}

	// �� ��ü �� �ϳ��� �̹� ���� ���¶��
	bool bDead = false;
	if (_leftObject->IsDead() || _rightObject->IsDead())
	{
		bDead = true;
	}

	// Collision Check Between Collider
	if (CollisionBtwCollider(LeftObjCollider2D, RightObjCollider2D))
	{
		// ���� Tick ������ �浹 ���¿���.
		if (bDead && iter->second) // ������ �浹 �� �̾����� ��ü�� ���� ���� ������ ���
		{
			LeftObjCollider2D->EndOverlap(RightObjCollider2D);
			RightObjCollider2D->EndOverlap(LeftObjCollider2D);
			iter->second = false;
		}
		else if (iter->second) // ������ �浹 ���̾����� �� ��ü ��� ����ִ� ���
		{
			LeftObjCollider2D->OnOverlap(RightObjCollider2D);
			RightObjCollider2D->OnOverlap(LeftObjCollider2D);
		}
		else
		{
			// ���� �����ӿ��� �浹�� �ƴϾ����� �̹��� �浹�ϴ� ���
			if(!bDead)
			{
				LeftObjCollider2D->BeginOverlap(RightObjCollider2D);
				RightObjCollider2D->BeginOverlap(LeftObjCollider2D);
				iter->second = true;
			}
		}
	}
	else // �浹 ���°� �ƴ� ���
	{
		if (iter->second) // ���� �浹 ���°� �ƴѵ� �浹 ���̶�� ����Ǿ� �ִ� ���
		{
			LeftObjCollider2D->EndOverlap(RightObjCollider2D);
			RightObjCollider2D->EndOverlap(LeftObjCollider2D);
			iter->second = false;
		}
	}
}

bool CCollisionMgr::CollisionBtwCollider(CCollider2D* _leftCollider, CCollider2D* _rightCollider)
{
	// ���� ��ġ
	Vec3 arrLocal[4] =
	{
		Vec3(-0.5f, 0.5f, 0.f),
		Vec3(0.5f, 0.5f, 0.f),
		Vec3(0.5f, -0.5f, 0.f),
		Vec3(-0.5f, -0.5f, 0.f),
	};

	// �� �浹ü�� �� ���� ���⺤�͸� ���Ѵ�.
	Vec3 arrProj[4] = {};

	arrProj[0] = XMVector3TransformCoord(arrLocal[1], _leftCollider->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _leftCollider->GetColliderWorldMat());
	arrProj[1] = XMVector3TransformCoord(arrLocal[3], _leftCollider->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _leftCollider->GetColliderWorldMat());

	arrProj[2] = XMVector3TransformCoord(arrLocal[1], _rightCollider->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _rightCollider->GetColliderWorldMat());
	arrProj[3] = XMVector3TransformCoord(arrLocal[3], _rightCollider->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _rightCollider->GetColliderWorldMat());

	// �� �浹ü�� �߽��� ������ ����
	Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _rightCollider->GetColliderWorldMat()) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _leftCollider->GetColliderWorldMat());

	// �и��� üũ
	for (int i = 0; i < 4; ++i)
	{
		Vec3 vProj = arrProj[i];
		vProj.Normalize(); // �и����� ����ȭ

		float fProjDist = 0.f; // �и��࿡ 4���� ���⺤�Ͱ� ������ ���̵��� ��
		for (int j = 0; j < 4; ++j) // ...��)
		{
			fProjDist += fabsf(arrProj[j].Dot(vProj)); // ���⺤�� arrProj[j] �� �и��� ���� vProj �� ������ �Ÿ� �� 4 ���� ���Ѵ�.
		}

		fProjDist /= 2.f; // 4���� ������ �����Ÿ��� �������� ������.

		float fCenter = fabsf(vCenter.Dot(vProj)); // �� �浹ü�� �߾��� ���� ���� ���͸� �и��� ���� vProj �� �������� ���� �Ÿ��̴�.

		if (fProjDist < fCenter) // �� ���� �и��� �߿� �߾��� ������ ���� ���Ͱ� ������ �Ÿ����� �и��࿡ �װ��� ���� ���͸� ������ �Ÿ��� �� ���� ū �и����� �ϳ��� �����Ѵٸ� �浹���� �ʾҴٰ� �Ǻ��Ѵ�.
		{
			return false;
		}
	}

	return true;;
}
