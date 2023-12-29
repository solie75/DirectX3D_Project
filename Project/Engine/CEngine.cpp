#include "pch.h"
#include "CEngine.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CDevice.h"


CEngine::CEngine()
    : m_hWnd(nullptr)
    , m_vPosition(0.f, 0.f)
    , m_MovingDist(0.2f)
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

    // Manager Init

    CPathMgr::GetInst()->PathMgrInit();
    CKeyMgr::GetInst()->KeyMgrInit();
    CTimeMgr::GetInst()->TimeMgrInit();

    // Device Init
    CDevice::GetInst()->DeviceInit(m_hWnd, m_vResolution.x, m_vResolution.y);

    // Shader Init
    m_Shader = new CShader;
    m_Shader->ShaderInit();

    // Create Mesh
    CreateMesh();

    CB = new CConstBuffer(0);
    CB->CreateCB(sizeof(TransPos), 1);

    return S_OK;
}

void CEngine::EngineProgress()
{
    EngineTick();
    EngineRender();
}

void CEngine::CreateMesh()
{
    vector<Vtx> vecVtx;
    vector<UINT> vecIdx;
    Vtx v;

    // Set RectMesh
    v.vPos = Vec3(-0.5f, 0.5f, 0.f);
    v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
    vecVtx.push_back(v);

    v.vPos = Vec3(0.5f, 0.5f, 0.f);
    v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
    vecVtx.push_back(v);

    v.vPos = Vec3(0.5f, -0.5f, 0.f);
    v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
    vecVtx.push_back(v);

    v.vPos = Vec3(-0.5f, -0.5f, 0.f);
    v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
    vecVtx.push_back(v);

    vecIdx.push_back(0);
    vecIdx.push_back(2);
    vecIdx.push_back(3);

    vecIdx.push_back(0);
    vecIdx.push_back(1);
    vecIdx.push_back(2);

    // Create Mesh
    m_RectMesh = new CMesh;
    m_RectMesh->CreateMesh(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());

    vecVtx.clear();
    vecIdx.clear();
}

void CEngine::MovePosition()
{
    if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::TAP)
    {
        m_vPosition.x -= m_MovingDist;
    }
    if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::TAP)
    {
        m_vPosition.x += m_MovingDist;
    }
    if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::TAP)
    {
        m_vPosition.y += m_MovingDist;
    }
    if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::TAP)
    {
        m_vPosition.y -= m_MovingDist;
    }
    TransPos transPos;
    transPos.TransPosX = m_vPosition.x;
    transPos.TransPosY = m_vPosition.y;
    CB->SetCBData(&transPos);
}

void CEngine::EngineTick()
{
    // Manager Tick
    CTimeMgr::GetInst()->TimeMgrTick();
    CKeyMgr::GetInst()->KeyMgrTick();
    MovePosition();
    CB->UpdateCBData();
    m_Shader->UpdateShaderDate();
}

void CEngine::EngineRender()
{
    CTimeMgr::GetInst()->TimeMgrRender();
    CDevice::GetInst()->ClearTarget();

    CDevice::GetInst()->OMSet();

    m_RectMesh->RenderMesh();
}