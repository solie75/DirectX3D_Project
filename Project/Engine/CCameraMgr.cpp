#include "pch.h"
#include "CCameraMgr.h"
#include "CTransform.h"
#include "CCamera.h"
#include "CCameraMoveScript.h"

CCameraMgr::CCameraMgr()
{
}

CCameraMgr::~CCameraMgr()
{
}


const CGameObject* CCameraMgr::GetCamera(const wstring& _camName)
{
    map<wstring, CGameObject*>::iterator iter = m_mapCam.find(_camName);

    if (iter == m_mapCam.end())
    {
        return nullptr;
    }
    else
    {
        return iter->second;
    }

    return nullptr;
}

void CCameraMgr::AddCamera(const wstring& _camName, CGameObject* _cam)
{
    //m_mapCam.insert(std::make_pair(_camName, _cam));
    return;
}

void CCameraMgr::ResetMainCamera()
{
   map<wstring, CGameObject*>::iterator iter = m_mapCam.find(L"Main_Camera");
    if (iter != m_mapCam.end())
    {
        CTransform* tempCam = iter->second->GetComponent<CTransform>(COMPONENT_TYPE::TRANSFORM);
        tempCam->SetWorldPos(Vec3(0.f, 0.f, 0.f));
        tempCam->SetWorldRot(Vec3(0.f, 0.f, 0.f));
    }
}

void CCameraMgr::CameraMgrInit()
{
    // Main Camera
    CGameObject* tempCam = new CGameObject;
    tempCam->SetName(L"Main_Camera");
    CTransform* tempTF = new CTransform;
    tempTF->SetWorldPos(Vec3(0.f, 0.f, -500.f));
    tempCam->AddComponent(tempTF);
    CCamera* camComp = new CCamera;
    
    camComp->SetCameraType(CAMERA_TYPE::MAIN);
    camComp->SetLayerMaskAll(true);
    camComp->SetLayerMask((UINT)LAYER_TYPE::LAYER_UI, false);

    tempCam->AddComponent(camComp);
    tempCam->AddComponent(new CCameraMoveScript);

    m_mapCam.insert(make_pair(L"Main_Camera", tempCam));

    // UI Camera
    tempCam = new CGameObject;
    tempCam->SetName(L"UI_Camera");
    tempTF = new CTransform;
    tempTF->SetWorldPos(Vec3(0.f, 0.f, -500.f));
    tempCam->AddComponent(tempTF);

    camComp = new CCamera;
    camComp->SetCameraType(CAMERA_TYPE::UI);
    camComp->SetLayerMask((UINT)LAYER_TYPE::LAYER_UI, true);
    tempCam->AddComponent(camComp);
    m_mapCam.insert(make_pair(L"UI_Camera", tempCam));

    // Editor Camera
    //m_EditCam = new CGameObject;
    //tempCam->SetName(L"Editor_Camera");
    //tempTF = new CTransform;
    //tempTF->SetWorldPos(Vec3(0.f, 0.f, -500.f)); // UI 카메라와 위치는 같아야 하지 않을까
    //tempCam->AddComponent(tempTF);

    //camComp = new CCamera;
    //camComp->SetCameraType(CAMERA_TYPE::EDITOR);
    //camComp->SetLayerMask((UINT)COLLIDER_TYPE::LAYER_EDITOR, true);
    //tempCam->AddComponent(camComp);
}

void CCameraMgr::CameraMgrTick()
{
    map<wstring, CGameObject*>::iterator iter = m_mapCam.begin();
    for (; iter != m_mapCam.end(); ++iter)
    {
        iter->second->ObjTick();
    }
}

void CCameraMgr::CameraMgrFinalTick()
{
    map<wstring, CGameObject*>::iterator iter = m_mapCam.begin();
    for (; iter != m_mapCam.end(); ++iter)
    {
        iter->second->ObjFinaltick(); // Camera 객체의 FinalTick
        CCamera* tempCam = iter->second->GetComponent<CCamera>(COMPONENT_TYPE::CAMERA);
        tempCam->SortObject();
    }
}

void CCameraMgr::CameraMgrRender()
{
    map<wstring, CGameObject*>::iterator iter = m_mapCam.begin();
    for (; iter != m_mapCam.end(); ++iter)
    {
        CCamera* tempCam = iter->second->GetComponent<CCamera>(COMPONENT_TYPE::CAMERA);
        tempCam->CameraRender();
    }
}

//void CCameraMgr::SetEditCam(CGameObject* _editCam)
//{
//    m_EditCam = _editCam;
//}

