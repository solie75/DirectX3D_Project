#include "pch.h"
#include "CGameObject.h"

CGameObject::CGameObject()
    : m_bDead(false)
    , m_pRenderComp(nullptr)
{
}

CGameObject::CGameObject(const CGameObject& _other)
    : CEntity(_other)
    , m_bDead(false)
    , m_pRenderComp(_other.m_pRenderComp)
{
    // Copy Component
    for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
    {
        if (_other.m_arrComp[i])
        {
            AddComponent(_other.m_arrComp[i]->Clone());
        }
    }
}

CGameObject::~CGameObject()
{
    Safe_Del_Array(m_arrComp); // ...s)
}

void CGameObject::ObjInit()
{
}

void CGameObject::ObjTick()
{
    for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
    {
        if (m_arrComp[i] != nullptr)
        {
            m_arrComp[i]->CompTick();
        }
    }
}

void CGameObject::ObjFinaltick()
{  
}

void CGameObject::ObjRender()
{
    /*for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
    {
        if (m_arrComp[i] != nullptr)
        {
            m_arrComp[i]->CompRender();
        }
    }*/

    if (nullptr != m_pRenderComp)
    {
        m_pRenderComp->CompRender();
    }
}

void CGameObject::AddComponent(CComponent* _component)
{
    _component->SetOwnerObj(this);

    // 전달된 인자가 이미 보유하고 있는 컴포넌트의 경우
    assert(!m_arrComp[(UINT)_component->GetComponentType()]);
    
    // 전달된 인자가 보유하지 않은 컴포넌트인 경우
    if (_Compoennt)
    {
        assert(!m_pRenderComp);
        m_pRenderComp = (CRenderComponent*)_component;
    }
    else
    {
        m_arrComp[(UINT)_component->GetComponentType()] = _component;
    }
}

//CComponent* CGameObject::GetComponent(COMPONENT_TYPE _type)
//{
//    return nullptr;
//}
