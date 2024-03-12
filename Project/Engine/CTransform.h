#pragma once
#include "CComponent.h"

class CTransform :
    public CComponent
{
public:
    CTransform();
    ~CTransform();

    CLONE(CTransform);

private:
    Vec3 m_vWorldPos;
    Vec3 m_vWorldScale;
    Vec3 m_vWorldRot;

    Matrix m_matWorld;
    Matrix m_matWordTransScale;

    // World Space 상에서 물체가 바라보고 있는 방향 (Local Space 상에서 기본적으로 바라보고 있는 방향을 
    // Vec3[3] = {Vec3(1.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f), Vec3(0.f, 0.f, 1.f} 라고 할때)
    Vec3 m_vWorldDir[3]; 
    
public:
    void SetWorldPos(Vec3 _pos);
    void SetWorldScale(Vec3 _scale);
    void SetWorldRot(Vec3 _rot);
    
    Vec3 GetWorldPos() const;
    Vec3 GetWorldScale() const;
    Vec3 GetWorldRot() const;
    Vec3 GetWorldDir(DIR_TYPE _type);
    const Matrix& GetWorldMat();

    void SetWorldMat(const Matrix& _mat);

public:
    void CompInit() override;
    void CompTick() override;
    void CompFinalTick() override;

    void TransUpdateData();
};
