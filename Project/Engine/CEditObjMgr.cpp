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

	// CameraMgr 의 Editor Camera Render 가 호출했을 때 현재 함수는
	// 두개의 Debug Shape Edit Object 의 Transform 값을 Debug Info 의 값에 따라 변경 해주면서
	// 각 객체의 RenderComp->Render() 를 호출한다.

	m_vecDebugShapeInfo.clear();
}

void CEditObjMgr::SetMainCamData(tTransform_CB _data)
{
	MainCamData = _data;
}

// 그럼 debug Obj 를 domain 으로 분류해야된다는 건가...?
// Debug 에서 분류해야 할 것은 Domain 별이 아니지 않나?
// Sort Object 의 기준이 달라야 한다.
// => debug Obj 는 결국 Collider Type 으로 분류되어야 하는 것 아닌가?
// -> debug Obj 가 어떤 Collider 를 출력할지에 대한 여부.
// 그럼 카메라를 하나 늘려.... => 이건 별로 상관 없을 것 같은데...
// 아니면 Camera 의 낷 Object 에서 

// CEditObj 가 별도로 가지고 있는게 맞다. 아니면 별도의 Edit Camera 를 Camera 가 따로 가지고 있어야 한다.
