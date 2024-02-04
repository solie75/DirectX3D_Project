#pragma once
#include "CEntity.h"

class CGameObject;

#define GET_OTHER_COMPONENT(type) C##type* Get##type() (return m_pOwner->Get##type();)

class CComponent :
    public CEntity
{
private:
    CGameObject* m_pOwner;
    const COMPONENT_TYPE m_Type;

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

    //virtual void CompRender() = 0; // ���Ŀ� Transform �� 
    CComponent* Clone() = 0; // Component ���� �����ڿ��� ���Ǳ� ����

public:
    template <typename T>
    T* GetOtherComp(COMPONENT_TYPE _type);

    //GET_OTHER_COMPONENT(Transform);
};

template<typename T>
inline T* CComponent::GetOtherComp(COMPONENT_TYPE _type)
{
    return m_pOwner->GetComponent<T>(_type);
}
