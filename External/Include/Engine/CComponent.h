#pragma once
#include "CEntity.h"

class CGameObject;

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

    void CompInit();
    void CompTick();
    void CompFinalTick(); // 왜 Final tick 을 순수가상함수로 두는 걸까? 각자 필요에 따라 넣으면 되는거 아닌가?
    // 너무 기능을 Tick 말고 FinalTick() 에만 몰아 넣는것 아닌가?

    virtual void CompRender() = 0; // 추후에 Transform 등 


    CComponent* Clone() = 0; // Component 복사 생성자에서 사용되기 때문
};

