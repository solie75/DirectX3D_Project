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

	bool m_bManagedByEngine;// 후에 사용자가 런타이미에 메쉬를 만들어 추가할때 기존의 default 로 생성되어 관리되던 Mesh 들과 구분되기 위한 값


private:
	void SetKey(const wstring _key) { m_strKey = _key; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

	void AddRefCount() { ++m_iRefCount; }
	void Release();

public:
	// 리소스는 Clone 구현하지 않음
	virtual CRes* Clone() { return nullptr;}

public:
	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }
	RES_TYPE GetResType() { return m_ResType; }
	bool IsEnginesRes() { return m_bManagedByEngine; }

private:
	virtual HRESULT LoadRes(const wstring& _strFilePath) = 0;

public:
	virtual HRESULT SaveRes(const wstring& _strFilePath) = 0;

public:
	CRes(RES_TYPE _type, bool _bEngine = false);
	CRes(const CRes& _Other);
	virtual ~CRes();

	friend class CResMgr;

	template<typename T>
	friend class Ptr;
};

