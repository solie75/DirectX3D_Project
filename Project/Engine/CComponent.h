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
    void CompFinalTick(); // �� Final tick �� ���������Լ��� �δ� �ɱ�? ���� �ʿ信 ���� ������ �Ǵ°� �ƴѰ�?
    // �ʹ� ����� Tick ���� FinalTick() ���� ���� �ִ°� �ƴѰ�?

    virtual void CompRender() = 0; // ���Ŀ� Transform �� 


    CComponent* Clone() = 0; // Component ���� �����ڿ��� ���Ǳ� ����
};

