#pragma once
#include "ptr.h"
#include "CRes.h"
#include "CMesh.h"
#include "CShader.h"
#include "CTexture.h"
#include "CMaterial.h"

class CResMgr
	: public CSingleton<CResMgr>
{
	SINGLE(CResMgr)
private:
	map<wstring, Ptr<CRes>> m_arrRes[(UINT)RES_TYPE::END];
	//bool m_changed; // �̰� ��� ���� ����? -> ContentUI ���� ResetContent() �� ȣ���ϴ� �����̵ȴ�. �ϴ��� �ּ�ó��

public:
	void ResMgrInit();
	void ResMgrTick();

private:
	void CreateDefaultMesh();
	void CreateDefaultShader();
	void CreateDefaultMaterial();
	void LoadDefaultTexture();

public:
	template<typename T>
	Ptr<T> FindRes(const wstring& _resKey);

	template<typename T>
	void AddRes(const wstring& _resKey, Ptr<T>& _res);

	const map<wstring, Ptr<CRes>>& GetResMap(RES_TYPE _resType) { return m_arrRes[(UINT)_resType]; }

private:
	void DeleteRes(RES_TYPE _type, const wstring& _strKey);
};

template<typename T>
RES_TYPE GetResType()
{
    if (typeid(T).hash_code() == typeid(CMesh).hash_code())
        return RES_TYPE::MESH;
    if (typeid(T).hash_code() == typeid(CShader).hash_code())
        return RES_TYPE::SHADER;
	if (typeid(T).hash_code() == typeid(CTexture).hash_code())
		return RES_TYPE::TEXTURE;
	if (typeid(T).hash_code() == typeid(CMaterial).hash_code())
		return RES_TYPE::MATERIAL;

    return RES_TYPE::END;
}

template<typename T>
inline Ptr<T> CResMgr::FindRes(const wstring& _resKey)
{
	RES_TYPE resType = GetResType<T>();
	map<wstring, Ptr<CRes>>::iterator resIter = m_arrRes[(UINT)resType].find(_resKey);
	if (resIter == m_arrRes[(UINT)resType].end())
	{
		return nullptr;
	}

	return (T*)resIter->second.Get();
}

template<typename T>
inline void CResMgr::AddRes(const wstring& _resKey, Ptr<T>& _res)
{
	// �̹� �ش� Key �� resource �� ����Ǿ� �ִ� ���
	assert(!(FindRes<T>(_resKey).Get()));

	RES_TYPE type = GetResType<T>();
	m_arrRes[(UINT)type].insert(make_pair(_resKey, _res.Get()));
	_res->SetKey(_resKey); // ���� ����Ǵ� ��� res �� �ڱ��� Key �� �˰� ����
}
