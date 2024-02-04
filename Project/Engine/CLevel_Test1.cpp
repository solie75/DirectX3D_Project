#include "pch.h"
#include "CLevel_Test1.h"
#include "CMeshRender.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CTransform.h"

CLevel_Test1::CLevel_Test1()
    : CLevel(LEVEL_TYPE::LEVEL_TYPE_TEST1)
{
}

CLevel_Test1::~CLevel_Test1()
{
}

void CLevel_Test1::LevelInit()
{
	CGameObject* ObjTest1 = new CGameObject;
	AddGameObj(ObjTest1, (UINT)LAYER_TYPE::LAYER_TEXTURE);

    CMeshRender* tempMeshRender = new CMeshRender;
    tempMeshRender->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
    tempMeshRender->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DefaultMtrl1"));
    
    ObjTest1->AddComponent(tempMeshRender);

    CGameObject* CameraObj = new CGameObject;
    CameraObj->SetName(L"CameraObj");
    AddGameObj(CameraObj, (UINT)LAYER_TYPE::LAYER_TEXTURE);
    CameraObj->AddComponent(new CCamera);
    CameraObj->AddComponent(new CTransform);

}

void CLevel_Test1::LevelTick()
{
    CLevel::LevelTick();
}

void CLevel_Test1::LevelFinaltick()
{
    CLevel::LevelFinaltick();
}

void CLevel_Test1::LevelRender()
{
    CLevel::LevelRender();
}