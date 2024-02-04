#include "pch.h"
#include "CTransform.h"
#include "CConstBuffer.h"
#include "CDevice.h"

CTransform::CTransform()
    : CComponent(COMPONENT_TYPE::TRANSFORM)
    , m_vWorldScale(Vec3(1.f, 1.f, 1.f))
    , m_vWorldDir{
        Vec3(1.f, 0.f, 0.f),
        Vec3(0.f, 1.f, 0.f),
        Vec3(0.f, 0.f, 1.f)}
{
    SetName(L"Transform");
}

CTransform::~CTransform()
{
}

void CTransform::SetWorldPos(Vec3 _pos)
{
    m_vWorldPos = _pos;
}

void CTransform::SetWorldScale(Vec3 _scale)
{
    m_vWorldScale = _scale;
}

void CTransform::SetWorldRot(Vec3 _rot)
{
    m_vWorldPos = _rot;
}

Vec3 CTransform::GetWorldPos() const
{
    return m_vWorldPos;
}

Vec3 CTransform::GetWorldScale() const
{
    return m_vWorldScale;
}

Vec3 CTransform::GetWorldRot() const
{
    return m_vWorldRot;
}

Vec3 CTransform::GetWorldDir(DIR_TYPE _type)
{
    return m_vWorldDir[(UINT)_type];
}

void CTransform::SetWordMat(const Matrix& _mat)
{
    m_matWorld = _mat;
}

void CTransform::CompInit()
{
}

void CTransform::CompTick()
{
    // Tick �ܰ� ������ ����� Pos, Scale, Rot ��ġ�� �ɹ� ������ �����Ѵ�.
}

void CTransform::CompFinalTick()
{
    m_matWordTransScale = XMMatrixIdentity();
    m_matWordTransScale = XMMatrixScaling(m_vWorldScale.x, m_vWorldScale.y, m_vWorldScale.z);

    Matrix tempRotMat = XMMatrixIdentity();
    tempRotMat = XMMatrixRotationX(m_vWorldRot.x);
    tempRotMat *= XMMatrixRotationY(m_vWorldRot.y);
    tempRotMat *= XMMatrixRotationZ(m_vWorldRot.z);

    Matrix tempTransMat = XMMatrixTranslation(m_vWorldPos.x, m_vWorldPos.y, m_vWorldPos.z);

    m_matWorld = m_matWordTransScale * tempRotMat * tempTransMat;

    Vec3 vDefaultDir[3] = {
          Vec3(1.f, 0.f, 0.f)
        , Vec3(0.f, 1.f, 0.f)
        , Vec3(0.f, 0.f, 1.f)
    };

    for (int i = 0; i < 3; ++i)
    {
        m_vWorldDir[i] = XMVector3TransformNormal(vDefaultDir[i], tempRotMat);
    }
}

void CTransform::TransUpdateData()
{
    CConstBuffer* pTransfromBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
}
