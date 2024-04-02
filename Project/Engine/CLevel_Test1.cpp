#include "pch.h"
#include "CLevel_Test1.h"
#include "CMeshRender.h"
#include "CResMgr.h"
#include "CCollisionMgr.h"
#include "CCamera.h"
#include "CTransform.h"
#include "CAnimator2D.h"
//#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CCameraMoveScript.h"
#include "CSetColorShader.h"
#include "CCollider2D.h"

CLevel_Test1::CLevel_Test1()
    : CLevel(LEVEL_TYPE::LEVEL_TYPE_TEST1)
    //, m_pCamera(nullptr)
{
}

CLevel_Test1::~CLevel_Test1()
{
}

void CLevel_Test1::LevelInit()
{
    CLevel::LevelInit();

    // compute Shader Test
    Ptr<CTexture> pTestTex = new CTexture;
    pTestTex->SetName(L"TestTex");
    pTestTex->SetTexture2D(100, 100, DXGI_FORMAT_R8G8B8A8_UNORM,
        D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS, D3D11_USAGE_DEFAULT);
    CResMgr::GetInst()->AddRes<CTexture>(L"TestTex", pTestTex);

    Ptr<CSetColorShader> pCS = (CSetColorShader*)CResMgr::GetInst()->FindRes<CComputeShader>(L"SetColorCS").Get();
    pCS->SetTargetTexture(CResMgr::GetInst()->FindRes<CTexture>(L"TestTex"));
    pCS->SetColor(Vec3(0.f, 0.f, 1.f));
    pCS->ExecuteCS();

    CGameObject* testObj = new CGameObject;
    testObj->SetName(L"TestObj");
    
    // Transform
    CTransform* testTF = new CTransform;
    testTF->SetWorldPos(Vec3(-200.f, 0.f, 0.f));
    testTF->SetWorldScale(Vec3(100.f, 100.f, 1.f));
    testObj->AddComponent(testTF);

    // MeshRender
    CMeshRender* testMR = new CMeshRender;
    testMR->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DefaultMtrl1"));
    testMR->GetMaterial()->SetMtrlTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"TestTex"));
    testMR->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));

    testObj->AddComponent(testMR);

    // Collider
    CCollider2D* tempCD = new CCollider2D;
    // 절대적인 위치나 크기가 아니라 캐릭터에 대해 비례적으로 적용된다.
    tempCD->SetOffsetPos(Vec2(0.f, 0.f));
    tempCD->SetOffsetScale(Vec2(1.f, 1.f));

    testObj->AddComponent(tempCD);

    AddGameObj(testObj, (UINT)LAYER_TYPE::LAYER_TEST);

    CPlayer* player = new CPlayer;
    AddGameObj(player, (UINT)LAYER_TYPE::LAYER_PLAYER);

    CMonster* monster = new CMonster;
    AddGameObj(monster, (UINT)LAYER_TYPE::LAYER_MONSTER);

    CCollisionMgr::GetInst()->LayerCheck(UINT(LAYER_TYPE::LAYER_PLAYER), UINT(LAYER_TYPE::LAYER_MONSTER));
}

void CLevel_Test1::LevelTick()
{
    CLevel::LevelTick();
}

void CLevel_Test1::LevelFinaltick()
{
    CLevel::LevelFinaltick();
}

//void CLevel_Test1::LevelRender()
//{
//    CLevel::LevelRender();
//    m_pCamera->CameraRender();
//}