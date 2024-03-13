#pragma once
#include "CGameObject.h"
class CMonster :
    public CGameObject
{
public:
    CMonster();
    ~CMonster();

private:
    DIRECTION_TYPE m_directionType;
    OBJECT_STATE m_curState;

public:
    void ObjInit() override;
    void ObjTick() override;
    void ObjFinaltick() override;
    void ObjRender() override;

public:
    void SetDirectionType(DIRECTION_TYPE _type) { m_directionType = _type; }
    DIRECTION_TYPE GetCurDirectionType() { return m_directionType; }
};

