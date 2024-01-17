#include "pch.h"
#include "CGameObject.h"

CGameObject::CGameObject()
    : m_bDead(false)
{
}

CGameObject::CGameObject(const CGameObject& _other)
    : CEntity(_other)
    , m_bDead(false)
{
    // Copy Component
    for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
    {
        if (_other.m_arrCom[i])
        {
            AddComponent(_other.m_arrCom[i]->Clone());
        }
    }
}

CGameObject::~CGameObject()
{
    Safe_Del_Array(m_arrCom); // ...s)
}

void CGameObject::ObjBegin()
{
}

void CGameObject::ObjTick()
{
}

void CGameObject::ObjFinaltick()
{
}

void CGameObject::ObjRender()
{
}

void CGameObject::AddComponent(CComponent* _component)
{
}

CComponent* CGameObject::GetComponent(COMPONENT_TYPE _type)
{
    return nullptr;
}
