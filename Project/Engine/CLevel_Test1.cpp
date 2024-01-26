#include "pch.h"
#include "CLevel_Test1.h"
#include "CMeshRender.h"
#include "CResMgr.h"

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
	AddGameObj(ObjTest1, (UINT)LAYER_TYPE::LAYER_TYPE_TEST1);

    CMeshRender* tempMeshRender = new CMeshRender;
    //Ptr<CMesh> tempMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
    //tempMeshRender->SetMesh(tempMesh);
    tempMeshRender->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));

    //Ptr<CMaterial> tempMaterial = CResMgr::GetInst()->FindRes<CMaterial>(L"DefaultMtrl1");
    tempMeshRender->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DefaultMtrl1"));
    
    ObjTest1->AddComponent(tempMeshRender);
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