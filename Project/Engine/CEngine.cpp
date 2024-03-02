#include "pch.h"
#include "CEngine.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CDevice.h"
#include "CResMgr.h"
#include "CLevelMgr.h"
#include "CCameraMgr.h"

#include "CMeshRender.h"


CEngine::CEngine()
    : m_hWnd(nullptr)
    , m_vResolution(0.f, 0.f)
    , m_pGameObj(nullptr)
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
    CLevelMgr::GetInst()->LevelMgrInit();
    CCameraMgr::GetInst()->CameraMgrInit();

    // GameObject Init
    // CResMgr::ResMgrInit() 에서 생성된 Mesh 와 Material 을 가진 Mesh render 를 GameObject 에 추가한다.
 
    return S_OK;
}

void CEngine::EngineProgress()
{
    EngineTick();
    EngineFinalTick();
    EngineRender();
}

void CEngine::EngineTick()
{
    // Manager Tick
    CTimeMgr::GetInst()->TimeMgrTick();
    CKeyMgr::GetInst()->KeyMgrTick();
    CLevelMgr::GetInst()->LevelMgrTick();
    CCameraMgr::GetInst()->CameraMgrTick();
}

void CEngine::EngineFinalTick()
{
    CLevelMgr::GetInst()->LevelMgrFinalTick();
    CCameraMgr::GetInst()->CameraMgrFinalTick();
}

void CEngine::EngineRender()
{
    CTimeMgr::GetInst()->TimeMgrRender();
    CDevice::GetInst()->ClearTarget();

    CDevice::GetInst()->OMSet();
    //CLevelMgr::GetInst()->LevelMgrRender();
    CCameraMgr::GetInst()->CameraMgrRender();
}