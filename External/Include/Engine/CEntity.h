#pragma once
class CEntity
{
private:
	static UINT g_iNextID;

	wstring m_strName;
	const UINT m_iID;

public:
	void SetName(wstring _name) { m_strName = _name; }
	const wstring& GetName() { return m_strName; }
	UINT GetID() { return m_iID; }

public:
	virtual CEntity* Clone() = 0;

public:
	CEntity();
	CEntity(const CEntity& _other);
	virtual ~CEntity();
};

