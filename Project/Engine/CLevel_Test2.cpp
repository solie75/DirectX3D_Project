#include "pch.h"
#include "CLevel_Test2.h"
#include "CMeshRender.h"
#include "CResMgr.h"

CLevel_Test2::CLevel_Test2()
    : CLevel(LEVEL_TYPE::LEVEL_TYPE_TEST2)
{
}

CLevel_Test2::~CLevel_Test2()
{
}

void CLevel_Test2::LevelInit()
{
    CGameObject* ObjTest2 = new CGameObject;
    AddGameObj(ObjTest2, (UINT)LAYER_TYPE::LAYER_CAMERA);

    CMeshRender* tempMeshRender = new CMeshRender;
    //Ptr<CMesh> tempMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
    //tempMeshRender->SetMesh(tempMesh);
    tempMeshRender->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));

    //Ptr<CMaterial> tempMaterial = CResMgr::GetInst()->FindRes<CMaterial>(L"DefaultMtrl2");
    //tempMeshRender->SetMaterial(tempMaterial);
    tempMeshRender->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DefaultMtrl2"));

    ObjTest2->AddComponent(tempMeshRender);
}

void CLevel_Test2::LevelTick()
{
    CLevel::LevelTick();
}

void CLevel_Test2::LevelFinaltick()
{
    CLevel::LevelFinaltick();
}

//void CLevel_Test2::LevelRender()
//{
//    CLevel::LevelRender();
//}
