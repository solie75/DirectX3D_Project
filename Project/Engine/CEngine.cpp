#include "pch.h"
#include "CEngine.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CDevice.h"
#include "CResMgr.h"

#include "CMeshRender.h"


CEngine::CEngine()
    : m_hWnd(nullptr)
    , m_vResolution(0.f, 0.f)
    , m_pGameObj(nullptr)
    //, m_vPosition(0.f, 0.f)
    //, m_MovingDist(0.2f)
{
}

CEngine::~CEngine()
{
}

int CEngine::EngineInit(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
    m_hWnd = _hWnd;
    m_vResolution = Vec2((float)_iWidth, (float)_iHeight);

    RECT rt = { 0, 0, _iWidth, _iHeight };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
    ShowWindow(m_hWnd, true);

    // Device Init
    CDevice::GetInst()->DeviceInit(m_hWnd, m_vResolution.x, m_vResolution.y);

    // Manager Init

    CPathMgr::GetInst()->PathMgrInit();
    CKeyMgr::GetInst()->KeyMgrInit();
    CTimeMgr::GetInst()->TimeMgrInit();
    CResMgr::GetInst()->ResMgrInit();

    // GameObject Init
    // CResMgr::ResMgrInit() 에서 생성된 Mesh 와 Material 을 가진 Mesh render 를 GameObject 에 추가한다.
    m_pGameObj = new CGameObject;
    CMeshRender* tempMeshRender = new CMeshRender;
    Ptr<CMesh> tempMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
    tempMeshRender->SetMesh(tempMesh);
    Ptr<CMaterial> tempMaterial = CResMgr::GetInst()->FindRes<CMaterial>(L"DefaultMtrl");
    tempMeshRender->SetMaterial(tempMaterial);
    m_pGameObj->AddComponent(tempMeshRender);

    return S_OK;
}

void CEngine::EngineProgress()
{
    EngineTick();
    EngineRender();
}

//void CEngine::MovePosition()
//{
//    if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::TAP)
//    {
//        m_vPosition.x -= m_MovingDist;
//    }
//    if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::TAP)
//    {
//        m_vPosition.x += m_MovingDist;
//    }
//    if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::TAP)
//    {
//        m_vPosition.y += m_MovingDist;
//    }
//    if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::TAP)
//    {
//        m_vPosition.y -= m_MovingDist;
//    }
//    TransPos transPos;
//    transPos.TransPosX = m_vPosition.x;
//    transPos.TransPosY = m_vPosition.y;
//    CB->SetCBData(&transPos);
//}

void CEngine::EngineTick()
{
    // Manager Tick
    CTimeMgr::GetInst()->TimeMgrTick();
    CKeyMgr::GetInst()->KeyMgrTick();
    //MovePosition();
    //CB->UpdateCBData();

   /* Ptr<CMaterial> tempMaterial = CResMgr::GetInst()->FindRes<CMaterial>(L"DefaultMtrl");
    tempMaterial->UpdateMtrlData();*/

    // GameObject Tick
    m_pGameObj->ObjTick();

   /* Ptr<CShader> tempShader = CResMgr::GetInst()->FindRes<CShader>(L"Std2DShader"); // -> CMaterial::UpdateMtrlData() 에서 진행한다.
    tempShader->UpdateShaderDate();*/
}

void CEngine::EngineRender()
{
    CTimeMgr::GetInst()->TimeMgrRender();
    CDevice::GetInst()->ClearTarget();

    CDevice::GetInst()->OMSet();

   /* Ptr<CMesh> tempMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
    tempMesh->RenderMesh();*/

    m_pGameObj->ObjRender();
}