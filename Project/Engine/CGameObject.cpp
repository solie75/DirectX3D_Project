#include "pch.h"
#include "CGameObject.h"
#include "CRenderComponent.h"
#include "CScript.h"


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

    for (size_t i = 0; i < _other.m_vecScript.size(); ++i)
    {
        AddComponent(_other.m_vecScript[i]->Clone());
    }
}

CGameObject::~CGameObject()
{
    Safe_Del_Array(m_arrComp); // ...s)
    Safe_Del_Vec(m_vecScript);
}

void CGameObject::ObjInit()
{
    for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
    {
        if (m_arrComp[i] != nullptr)
        {
            m_arrComp[i]->CompInit();
        }
    }

    for (size_t i = 0; i < m_vecScript.size(); ++i)
    {
        m_vecScript[i]->ScriptInit();
    }
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

    for (size_t i = 0; i < m_vecScript.size(); ++i)
    {
        m_vecScript[i]->ScriptTick();
    }
}

void CGameObject::ObjFinaltick()
{  
    for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
    {
        if (m_arrComp[i] != nullptr)
        {
            m_arrComp[i]->CompFinalTick();
        }
    }

    for (size_t i = 0; i < m_vecScript.size(); ++i)
    {
        m_vecScript[i]->ScriptFinalTick();
    }
}

void CGameObject::ObjRender()
{
    if (nullptr != m_pRenderComp)
    {
        m_pRenderComp->CompRender();
    }
}

void CGameObject::AddComponent(CComponent* _component)
{
    _component->SetOwnerObj(this);

    // �߰��� ������Ʈ�� ��ũ��Ʈ�� ���
    if (COMPONENT_TYPE::SCRIPT == _component->GetComponentType())
    {
        m_vecScript.push_back((CScript*)_component);
    }
    else
    {
        // ���޵� ���ڰ� �̹� �����ϰ� �ִ� ������Ʈ�� ���
        assert(!m_arrComp[(UINT)_component->GetComponentType()]);

        // ���޵� ���ڰ� �������� ���� ������Ʈ�� ���
        if (_component->IsRenderComp())
        {
            assert(!m_pRenderComp);
            m_pRenderComp = (CRenderComponent*)_component;
        }
        else
        {
            m_arrComp[(UINT)_component->GetComponentType()] = _component;
        }
    }
}

