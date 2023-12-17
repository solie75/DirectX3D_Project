#include "pch.h"
#include "CRes.h"

void CRes::Release()
{
	--m_iRefCount;
	if (m_iRefCount == 0)
	{
		delete this;
	}
}

CRes::CRes(RES_TYPE _type, bool _bEngine)
	: m_ResType(_type)
	, m_bEngine(_bEngine)
	, m_iRefCount(0)
{
}

CRes::CRes(const CRes& _Other)
	: m_ResType(_Other.m_ResType)
	, m_bEngine(_Other.m_bEngine)
	, m_strKey(_Other.m_strKey)
	, m_strRelativePath(_Other.m_strRelativePath)
	, m_iRefCount(0)
{
}

CRes::~CRes()
{
}
