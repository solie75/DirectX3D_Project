#pragma once
#include "CShader.h"

class CGraphicsShader :
    public CShader
{
public:
    CGraphicsShader();
    ~CGraphicsShader();

private:
	ComPtr<ID3DBlob> m_VSBlob;
	ComPtr<ID3DBlob> m_PSBlob;
	ComPtr<ID3DBlob> m_GSBlob;


	ComPtr<ID3D11VertexShader> m_VS;
	ComPtr<ID3D11PixelShader> m_PS;
	ComPtr<ID3D11GeometryShader> m_GS;


	ComPtr<ID3D11InputLayout> m_Layout;
	D3D11_PRIMITIVE_TOPOLOGY m_eTopology;

	RS_TYPE m_RSType;
	DS_TYPE m_DSType;
	BS_TYPE m_BSType;

	DOMAIN_TYPE m_Domain;

public:
	//void ShaderInit();
	void CreateVertexShader(const wstring& _strFileName, const string& _strFuncName);
	void CreatePixelShader(const wstring& _strFileName, const string& _strFuncName);
	void CreateGeometryShader(const wstring& _strFileName, const string& _strFuncName);
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _topology);
	void UpdateShaderDate();

	void SetRSType(RS_TYPE _Type) { m_RSType = _Type; }
	void SetDSType(DS_TYPE _Type) { m_DSType = _Type; }
	void SetBSType(BS_TYPE _Type) { m_BSType = _Type; }
	void SetDomain(DOMAIN_TYPE _type) { m_Domain = _type; }
	DOMAIN_TYPE GetDomainType() { return m_Domain; }
};

