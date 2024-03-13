#include "pch.h"
#include "CEditObjMgr.h"
//#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "CResMgr.h"

CEditObjMgr::CEditObjMgr()
{
}

CEditObjMgr::~CEditObjMgr()
{
}

void CEditObjMgr::EditObjMgrInit()
{
	// Create Debug Shape Object
	m_DebugShape[(UINT)SHAPE_TYPE::RECT] = new CGameObject;
	m_DebugShape[(UINT)SHAPE_TYPE::RECT]->AddComponent(new CTransform);
	CMeshRender* tempMR = new CMeshRender;
	tempMR->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh_Debug"));
	tempMR->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DebugShapeMtrl"));
	m_DebugShape[(UINT)SHAPE_TYPE::RECT]->AddComponent(tempMR);

	tempMR = new CMeshRender;
	m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE] = new CGameObject;
	m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE]->AddComponent(new CTransform);
	tempMR->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CircleMesh_Debug"));
	tempMR->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DebugShapeMtrl"));
	m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE]->AddComponent(tempMR);
}

//void CEditObjMgr::EditObjMgrProgress()
//{
//	EditObjMgrTick();
//	EditObjMgrRender();
//}

//vector<tDebugShapeInfo>& CEditObjMgr::GetDebugShapeInfo()
//{
//	return m_vecDebugShapeInfo;
//}

void CEditObjMgr::AddDebugShapeInfo(tDebugShapeInfo _info)
{
	m_vecDebugShapeInfo.push_back(_info);
}

void CEditObjMgr::EditObjMgrFinalTick()
{
	// Editor Obj 는 결국 Camera 이다. 이건 CameraMgr 에서 관리할 일 아닌가?
	// 그럼 CameraMgr 의 Editor Camera Render 가 EditorObjMgrRender() 를 호출해야한다.
}

void CEditObjMgr::EditObjMgrRender()
{
	g_transform = MainCamData;

	CTransform* tempTR = nullptr;

	for (int i = 0; i < m_vecDebugShapeInfo.size(); i++)
	{
		if (m_vecDebugShapeInfo[i].eShape == SHAPE_TYPE::RECT)
		{
			tempTR = m_DebugShape[(UINT)SHAPE_TYPE::RECT]->GetComponent<CTransform>(COMPONENT_TYPE::TRANSFORM);
			tempTR->SetWorldMat(m_vecDebugShapeInfo[i].matWorld);

			m_DebugShape[(UINT)SHAPE_TYPE::RECT]->GetRenderComponent()->GetMaterial()->SetMtrlScalarParam(VEC4_0, m_vecDebugShapeInfo[i].vColor);
			m_DebugShape[(UINT)SHAPE_TYPE::RECT]->GetRenderComponent()->CompRender();
		}
		else if (m_vecDebugShapeInfo[i].eShape == SHAPE_TYPE::CIRCLE)
		{
			tempTR = m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE]->GetComponent<CTransform>(COMPONENT_TYPE::TRANSFORM);
			tempTR->SetWorldMat(m_vecDebugShapeInfo[i].matWorld);

			m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE]->GetRenderComponent()->GetMaterial()->SetMtrlScalarParam(VEC4_0, m_vecDebugShapeInfo[i].vColor);
			m_DebugShape[(UINT)SHAPE_TYPE::CIRCLE]->GetRenderComponent()->CompRender();
		}
	}

	m_vecDebugShapeInfo.clear();
}

void CEditObjMgr::SetMainCamData(tTransform_CB _data)
{
	MainCamData = _data;
}
