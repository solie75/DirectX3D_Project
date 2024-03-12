#pragma once
#include "CGameObject.h"

class CEditObjMgr
	: public CSingleton<CEditObjMgr>
{
	SINGLE(CEditObjMgr);

private:
	vector<CGameObject*> m_vecEditorObj; // ���� Render �Լ��� ����� �Ǵ� �ϳ��� ��ü

	CGameObject* m_DebugShape[(UINT)SHAPE_TYPE::END];
	vector<tDebugShapeInfo> m_vecDebugShapeInfo; // �ϳ��� edit Object �� ���� �ش� vector �� ��� ��Ҹ� ���� + Render �Ѵ�.

	UINT m_ColliderMask;

	tTransform_CB MainCamData;

public:
	void EditObjMgrInit();
	//void EditObjMgrProgress();

	//vector<tDebugShapeInfo>& GetDebugShapeInfo(); 
	void AddDebugShapeInfo(tDebugShapeInfo _info);
public:
	void EditObjMgrFinalTick();
	void EditObjMgrRender();
	void SetMainCamData(tTransform_CB _data);
};

