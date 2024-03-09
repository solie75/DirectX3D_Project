#pragma once
#include "CComponent.h"

class CState :
    public CComponent
{

public:
    CState();
    CState(UINT _iState, DIRECTION_TYPE _type);
    ~CState();

    CLONE(CState);

private:
    UINT m_CurState;
    UINT m_PrevState;
    DIRECTION_TYPE m_CurSightDir;
    DIRECTION_TYPE m_PrevSightDir;

public:
    UINT GetCurState();
    UINT GetPrevState();
    void SetCurState(UINT _iState);
    void SetCurState(UINT _iState, DIRECTION_TYPE _type);

    DIRECTION_TYPE GetCurDirectionType();
    DIRECTION_TYPE GetPrevDirectionType();
    void SetDirectionType(DIRECTION_TYPE _type);
};

