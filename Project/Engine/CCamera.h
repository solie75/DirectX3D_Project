#pragma once
#include "CComponent.h"
class CCamera :
    public CComponent
{
    CLONE(CCamera);

private:
    float m_fScale; // Orthographic 에서 사용하는 카메라 
    float m_fAspectRatio; // Perspective 에서 사용하는 카메라 종횡비


    PROJ_TYPE m_ProjType;
    CAMERA_TYPE m_CamType;
    
    Matrix m_matView;
    Matrix m_matProj;

    UINT m_iLayerMask;

    vector<CGameObject*>    m_vecOpaque;
    vector<CGameObject*>    m_vecMask;
    vector<CGameObject*>    m_vecTransparent;
    vector<CGameObject*>    m_vecUI;

public:
    CCamera();
    CCamera(const CCamera& _other);
    ~CCamera();

public:
    void CameraRender();
    void CompInit() override;
    void CompTick() override;
    void CompFinalTick() override;
    
private:
    void CalViewMat();
    void CalProjMat();

public:
    void SortObject();
    void ClearObject();

    void SetLayerMask(int _iLayer, bool _visible);
    void SetLayerMaskAll(bool _visible);
    void SetCameraType(CAMERA_TYPE _type);

private:
    void render_opaque();
    void render_mask();
    void render_transparent();
    void render_ui();
};

