#include "pch.h"
#include "CLevel_Test1.h"
#include "CMeshRender.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CTransform.h"
#include "CAnimator2D.h"
//#include "CGameObject.h"

#include "CCameraMoveScript.h"

CLevel_Test1::CLevel_Test1()
    : CLevel(LEVEL_TYPE::LEVEL_TYPE_TEST1)
    , m_pCamera(nullptr)
{
}

CLevel_Test1::~CLevel_Test1()
{
}

void CLevel_Test1::LevelInit()
{
    {   // Main Object
        CGameObject* ObjTest1 = new CGameObject;

        CTransform* tempTransform = new CTransform;
        tempTransform->SetWorldPos(Vec3(0.f, 0.f, 500.f)); // perspective 에서 z 값이 100 일때 와 500 일때
        tempTransform->SetWorldScale(Vec3(100.f, 100.f, 1.f)); // Orthographic 에서 Scale 이 변할때
        ObjTest1->AddComponent(tempTransform);

        CMeshRender* tempMeshRender = new CMeshRender;
        tempMeshRender->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
        tempMeshRender->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Ain2DMtrl"));
        ObjTest1->AddComponent(tempMeshRender);

        CAnimator2D* tempAnimator = new CAnimator2D;
        tAtlasData tempAtData;
        tempAtData.SpriteNum = 10;
        tempAtData.SpriteSize = Vec2(24, 41);
        tempAtData.TimePerSprite = 0.1f;
        tempAnimator->CreateAni2D(L"Will_Idle_Down", tempAtData);
        ObjTest1->AddComponent(tempAnimator);

        AddGameObj(ObjTest1, (UINT)LAYER_TYPE::LAYER_TEXTURE);

        tempAnimator->PlayAni2D(L"Will_Idle_Down", true);
    }

    {   // Main Camera
        CGameObject* CameraObj = new CGameObject;
        CameraObj->SetName(L"CameraObj");
        AddGameObj(CameraObj, (UINT)LAYER_TYPE::LAYER_TEXTURE);
        m_pCamera = new CCamera;
        CameraObj->AddComponent(m_pCamera);
        CameraObj->AddComponent(new CTransform);
        CameraObj->AddComponent(new CCameraMoveScript);
    }
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
    m_pCamera->CameraRender();
}