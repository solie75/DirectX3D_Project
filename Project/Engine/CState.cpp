#include "pch.h"
#include "CState.h"

CState::CState()
    : CComponent(COMPONENT_TYPE::STATE)
    , m_CurState(-1)
    , m_PrevState(-1)
    , m_CurSightDir(DIRECTION_TYPE::END)
    , m_PrevSightDir(DIRECTION_TYPE::END)
{
}

CState::CState(UINT _iState, DIRECTION_TYPE _type)
    : CComponent(COMPONENT_TYPE::STATE)
    , m_CurState(_iState)
    , m_PrevState(-1)
    , m_CurSightDir(_type)
    , m_PrevSightDir(DIRECTION_TYPE::END)
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

    SetDirectionType(_type);
}

DIRECTION_TYPE CState::GetCurDirectionType()
{
    return m_CurSightDir;
}

DIRECTION_TYPE CState::GetPrevDirectionType()
{
    return m_PrevSightDir;
}

void CState::SetDirectionType(DIRECTION_TYPE _type)
{
    m_PrevSightDir = m_CurSightDir;
    m_CurSightDir = _type;
}
