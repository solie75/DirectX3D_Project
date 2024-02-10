#pragma once
#include "CEntity.h"
#include "CGameObject.h"

#define GET_OTHER_COMPONENT(type) C##type* Get##type() (return m_pOwner->Get##type();)

class CComponent :
    public CEntity
{
private:
    CGameObject* m_pOwner;
    const COMPONENT_TYPE m_Type;

    bool m_bRender;

public:
    CComponent(COMPONENT_TYPE _type);
    CComponent(const CComponent& _other);
    virtual ~CComponent();

public:
    COMPONENT_TYPE GetComponentType();
    CGameObject* GetOwnerObj();
    void SetOwnerObj(CGameObject* _owner);

    virtual void CompInit();
    virtual void CompTick();
    virtual void CompFinalTick(); // �� Final tick �� ���������Լ��� �δ� �ɱ�? ���� �ʿ信 ���� ������ �Ǵ°� �ƴѰ�?
    // �ʹ� ����� Tick ���� FinalTick() ���� ���� �ִ°� �ƴѰ�?

    CComponent* Clone() = 0; // Component ���� �����ڿ��� ���Ǳ� ����

    bool IsRenderComp() { return m_bRender; }
    void SetBoolRenderComp(bool _b) { m_bRender = _b; }

public:
    template <typename T>
    T* GetOtherComp(COMPONENT_TYPE _type);
};

template<typename T>
inline T* CComponent::GetOtherComp(COMPONENT_TYPE _type)
{
    return m_pOwner->GetComponent<T>(_type);
}
