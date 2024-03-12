#pragma once
#include "CGameObject.h"

class CEditObjMgr
	: public CSingleton<CEditObjMgr>
{
	SINGLE(CEditObjMgr);

private:
	vector<CGameObject*> m_vecEditorObj; // 실제 Render 함수의 대상이 되는 하나의 객체

	CGameObject* m_DebugShape[(UINT)SHAPE_TYPE::END];
	vector<tDebugShapeInfo> m_vecDebugShapeInfo; // 하나의 edit Object 에 대해 해당 vector 의 모든 요소를 대입 + Render 한다.

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

