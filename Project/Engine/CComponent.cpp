#include "pch.h"
#include "CComponent.h"

CComponent::CComponent(COMPONENT_TYPE _type)
	: m_pOwner(nullptr)
	, m_Type(_type)
	, m_bRender(false)
{
}

CComponent::CComponent(const CComponent& _other)
	: CEntity(_other)
	, m_pOwner(nullptr)
	, m_Type(_other.m_Type)
	, m_bRender(_other.m_bRender)
{
}

CComponent::~CComponent()
{
}

COMPONENT_TYPE CComponent::GetComponentType()
{
	return m_Type;
}

CGameObject* CComponent::GetOwnerObj()
{
	return m_pOwner;
}

void CComponent::SetOwnerObj(CGameObject* _owner)
{
	m_pOwner = _owner;
}

void CComponent::CompInit()
{
}

void CComponent::CompTick()
{
}

void CComponent::CompFinalTick()
{
}
