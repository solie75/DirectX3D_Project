#include "pch.h"
#include "CState.h"

CState::CState()
    : CComponent(COMPONENT_TYPE::STATE)
    , m_CurState(-1)
    , m_PrevState(-1)
{
}

CState::CState(UINT _iState, DIRECTION_TYPE _type)
    : CComponent(COMPONENT_TYPE::STATE)
    , m_CurState(_iState)
    , m_PrevState(-1)
    , m_CurSightDir(_type)
{
}

CState::~CState()
{
}

UINT CState::GetCurState()
{
    return m_CurState;
}

UINT CState::GetPrevState()
{
    return m_PrevState;
}

void CState::SetCurState(UINT _iState)
{
    m_PrevState = m_CurState;
    m_CurState = _iState;
}

void CState::SetCurState(UINT _iState, DIRECTION_TYPE _type)
{
    m_PrevState = m_CurState;
    m_CurState = _iState;

    m_CurSightDir = _type;
}

DIRECTION_TYPE CState::GetDirectionType()
{
    return DIRECTION_TYPE();
}

void CState::SetDirectionType(DIRECTION_TYPE _type)
{
}
