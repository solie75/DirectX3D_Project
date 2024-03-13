#pragma once

class CLayer;
class CCollider2D;
class CGameObject;

union CollisionID
{
	struct
	{
		UINT LeftID;
		UINT RightID;
	};

	UINT_PTR id;
};

class CCollisionMgr
	: public CSingleton<CCollisionMgr>
{
	SINGLE(CCollisionMgr);

private:
	UINT m_matrix[(UINT)LAYER_TYPE::END];
	map<UINT_PTR, bool> m_mapColID;

public:
	void LayerCheck(UINT _left, UINT _right);
	//void LayerCheck(const wstring& _strLeftLayer, const wstring& _strRightLayer);
	void Clear();

public:
	void CollisionMgrTick();

private:
	void CollisionBtwLayer(CLayer* _leftLayer, CLayer* _rightLayer);
	void CollisionBtwObject(CGameObject* _leftObject, CGameObject* _rightObject);
	bool CollisionBtwCollider(CCollider2D* _leftCollider, CCollider2D* _rightCollider);
};