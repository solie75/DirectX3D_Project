#pragma once
#include "CEntity.h"

class CRes
	: public CEntity
{
private:
	const RES_TYPE m_ResType;
	UINT m_iRefCount;

	wstring m_strKey;
	wstring m_strRelativePath;

	bool m_bEngine;

private:
	void SetResKey(const wstring _key) { m_strKey = _key; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

	void AddRefCount() { ++m_iRefCount; }
	void Release();

public:
	// 리소스는 Clone 구현하지 않음
	virtual CRes* Clone() { return nullptr;}

public:
	const wstring& GetResKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }
	RES_TYPE GetResType() { return m_ResType; }
	bool IsEnginesRes() { return m_bEngine; }

private:
	virtual HRESULT LoadRes(const wstring& _strFilePath) = 0;

public:
	virtual HRESULT SaveRes(const wstring& _strFilePath) = 0;

public:
	CRes(RES_TYPE _type, bool _bEngine = false);
	CRes(const CRes& _Other);
	virtual ~CRes();

	friend class Ptr;
};

