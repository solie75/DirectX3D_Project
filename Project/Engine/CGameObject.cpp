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
    for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
    {
        if (m_arrCom[i] != nullptr)
        {
            m_arrCom[i]->CompTick();
        }
    }
}

void CGameObject::ObjFinaltick()
{  
}

void CGameObject::ObjRender()
{
    for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
    {
        if (m_arrCom[i] != nullptr)
        {
            m_arrCom[i]->CompRender();
        }
    }
}

void CGameObject::AddComponent(CComponent* _component)
{
    // 전달된 인자가 이미 보유하고 있는 컴포넌트의 경우
    assert(!m_arrCom[(UINT)_component->GetComponentType()]);
    
    // 전달된 인자가 보유하지 않은 컴포넌트인 경우
    m_arrCom[(UINT)_component->GetComponentType()] = _component;

    _component->SetOwnerObj(this);
}

//CComponent* CGameObject::GetComponent(COMPONENT_TYPE _type)
//{
//    return nullptr;
//}
