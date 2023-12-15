#include "pch.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::PathMgrInit()
{
	GetCurrentDirectory(256, m_szContentPath);

	// 상위 폴더로의 이동
	UINT iLen = (int)wcslen(m_szContentPath);

	for (int i = iLen - 1; i >= 0; --i)
	{
		if (L'\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = 0;
			break;
		}
	}

	wcscat_s(m_szContentPath, L"\\bin\\content\\");
}
