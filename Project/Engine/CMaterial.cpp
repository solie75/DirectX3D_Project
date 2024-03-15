#include "pch.h"
#include "CMaterial.h"
#include "CPathMgr.h"
#include "CConstBuffer.h"
#include "CDevice.h"

CMaterial::CMaterial(bool _bEngine)
    : CRes(RES_TYPE::MATERIAL)
    , m_MtrlConst{}
    , m_arrTex{}
{
}

CMaterial::~CMaterial()
{
}

//HRESULT CMaterial::LoadRes(const wstring& _strFilePath)
//{
//	if (IsEnginesRes())
//	{
//		return E_FAIL;
//	}
//
//	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
//	strFilePath += _strFilePath;
//
//	FILE* pFile = nullptr;
//	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
//
//	// Entity
//	SaveWString(GetName(), pFile);
//
//	return E_NOTIMPL;
//}
//
//HRESULT CMaterial::SaveRes(const wstring& _strFilePath)
//{
//	return E_NOTIMPL;
//}

HRESULT CMaterial::LoadRes(const wstring& _strFilePath)
{
	return S_OK;
}

HRESULT CMaterial::SaveRes(const wstring& _strFilePath)
{
	return S_OK;
}

void CMaterial::SetShader(Ptr<CGraphicsShader> _shader)
{
	m_pShader = _shader;
}

Ptr<CGraphicsShader> CMaterial::GetShader()
{
    return m_pShader;
}

void CMaterial::SetMtrlScalarParam(MATERIAL_SCALAR_PARAM _param, const void* _src)
{
	switch (_param)
	{
	case INT_0:
	case INT_1:
	case INT_2:
	case INT_3:
		m_MtrlConst.arrInt[_param] = *((int*)_src);
		break;
	case FLOAT_0:
	case FLOAT_1:
	case FLOAT_2:
	case FLOAT_3:
		m_MtrlConst.arrFloat[_param - FLOAT_0] = *((float*)_src);
		break;

	case VEC2_0:
	case VEC2_1:
	case VEC2_2:
	case VEC2_3:
		m_MtrlConst.arrV2[_param - VEC2_0] = *((Vec2*)_src);
		break;

	case VEC4_0:
	case VEC4_1:
	case VEC4_2:
	case VEC4_3:
		m_MtrlConst.arrV4[_param - VEC4_0] = *((Vec4*)_src);
		break;

	case MAT_0:
	case MAT_1:
	case MAT_2:
	case MAT_3:
		m_MtrlConst.arrMat[_param - MAT_0] = *((Matrix*)_src);
		break;
	}
}

void CMaterial::SetMtrlTexParam(MATERIAL_TEX_PARAM _param, const Ptr<CTexture>& _Tex)
{
    m_arrTex[(UINT)_param] = _Tex;
}

void CMaterial::GetMtrlScalarParam(MATERIAL_SCALAR_PARAM _param, void* _pData)
{
	switch (_param)
	{
	case INT_0:
	case INT_1:
	case INT_2:
	case INT_3:
	{
		int idx = (UINT)_param - (UINT)INT_0;
		*((int*)_pData) = m_MtrlConst.arrInt[idx];
	}
	break;
	case FLOAT_0:
	case FLOAT_1:
	case FLOAT_2:
	case FLOAT_3:
	{
		int idx = (UINT)_param - (UINT)FLOAT_0;
		*((float*)_pData) = m_MtrlConst.arrFloat[idx];
	}
	break;

	case VEC2_0:
	case VEC2_1:
	case VEC2_2:
	case VEC2_3:
	{
		int idx = (UINT)_param - (UINT)VEC2_0;
		*((Vec2*)_pData) = m_MtrlConst.arrV2[idx];
	}
	break;

	case VEC4_0:
	case VEC4_1:
	case VEC4_2:
	case VEC4_3:
	{
		int idx = (UINT)_param - (UINT)VEC4_0;
		*((Vec4*)_pData) = m_MtrlConst.arrV4[idx];
	}
	break;

	case MAT_0:
	case MAT_1:
	case MAT_2:
	case MAT_3:
	{
		int idx = (UINT)_param - (UINT)MAT_0;
		*((Matrix*)_pData) = m_MtrlConst.arrMat[idx];
	}
	break;
	}
}

Ptr<CTexture> CMaterial::GetTexParam(MATERIAL_TEX_PARAM _param)
{
    return m_arrTex[(UINT)_param];
}

void CMaterial::UpdateMtrlData()
{
	// Shader Update
	if (nullptr == m_pShader)
	{
		return;
	}

	m_pShader->UpdateShaderDate();

	// Texture Update
	for (UINT i = 0; i < TEX_END; ++i)
	{
		if (nullptr == m_arrTex[i]) // 텍스쳐가 존재하지 않는다면
		{
			m_MtrlConst.arrTex[i] = 0;
			CTexture::ClearTexRegister(i);
			//continue; // 원래는 여기 continue 를 활성화 한다 왜지?
		}
		else // 텍스쳐가 존재 한다면
		{
			m_MtrlConst.arrTex[i] = 1;
			m_arrTex[i]->UpdateTexData(i);
		}
	}

	CConstBuffer* pMtrlConstBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pMtrlConstBuffer->SetCBData(&m_MtrlConst);
	pMtrlConstBuffer->UpdateCBData();
}

