#pragma once
#include "CGameObject.h"

class CCameraMgr
	: public CSingleton<CCameraMgr>
{
	SINGLE(CCameraMgr);

private:
	map<std::wstring, CGameObject*> m_mapCam;
	//CGameObject* m_EditCam;

public:
	const CGameObject* GetCamera(const wstring& _camName);
	void AddCamera(const wstring& _camName, CGameObject* _cam);
	void ResetMainCamera();
	void CameraMgrInit();
	void CameraMgrTick();
	void CameraMgrFinalTick();
	void CameraMgrRender();

	//void SetEditCam(CGameObject* _editCam);
};