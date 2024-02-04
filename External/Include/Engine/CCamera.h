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
    
    Matrix m_matView;
    Matrix m_matProj;

    UINT m_iLayerMask;

    vector<CGameObject*> m_vecObject;

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
};

