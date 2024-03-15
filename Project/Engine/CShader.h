#pragma once
#include "CRes.h"
class CShader
	: public CRes
{
public:
	CShader(RES_TYPE _type);
	~CShader();

protected:
	ComPtr<ID3DBlob> m_ErrBlob;

public:
	virtual HRESULT SaveRes(const wstring& _strRelativePath) final { return S_OK; }
private:
	virtual HRESULT LoadRes(const wstring& _strFilePath) final { return S_OK; }

};

