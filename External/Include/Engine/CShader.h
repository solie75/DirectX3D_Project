#pragma once
class CShader
{
public:
	CShader();
	~CShader();

private:
	ComPtr<ID3DBlob> m_VSBlob;
	ComPtr<ID3DBlob> m_PSBlob;
	ComPtr<ID3DBlob> m_ErrBlob;

	ComPtr<ID3D11VertexShader> m_VS;
	ComPtr<ID3D11PixelShader> m_PS;

	ComPtr<ID3D11InputLayout> m_Layout;
	D3D11_PRIMITIVE_TOPOLOGY m_eTopology;

public:
	void ShaderInit();
	void CreateVertexShader(const wstring& _strFileName, const string& _strFuncName);
	void CreatePixelShader(const wstring& _strFileName, const string& _strFuncName);
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _topology);
	void UpdateShaderDate();
};

