#pragma once
#include "CComponent.h"
class CCollider2D :
    public CComponent
{
private:
    Vec3 m_vOffsetPos;
    Vec3 m_vOffsetScale;
    //bool m_bAbsolute; // 상대 이동, 크기를 절대값으로 지정.
    SHAPE_TYPE m_ShapeType;
    Matrix m_matWorldCollider2D;

    int m_iCollisionCount;
    bool m_bVisible;

public:
    CCollider2D();
    ~CCollider2D();

    CLONE(CCollider2D);

    virtual void CompFinalTick() override;

    void SetOffsetPos(Vec2 _vOffsetPos);
    void SetOffsetScale(Vec2 _vOffsetScale);
    //void SetBoolAbsolute(bool _v);

    void SetColider2DType(SHAPE_TYPE _type);

public:
    void BeginOverlap(CCollider2D* _other);
    void OnOverlap(CCollider2D* _other);
    void EndOverlap(CCollider2D* _other);
};

