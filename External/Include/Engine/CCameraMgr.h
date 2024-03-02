#pragma once
#include "CSingleton.h"
#include "CGameObject.h"

class CCameraMgr
	: public CSingleton<CCameraMgr>
{
	SINGLE(CCameraMgr);

private:
	map<std::wstring, CGameObject*> m_mapCam;

public:
	const CGameObject* GetCamera(const wstring& _camName);
	void AddCamera(const wstring& _camName, CGameObject* _cam);
	void ResetMainCamera();
	void CameraMgrInit();
	void CameraMgrTick();
	void CameraMgrFinalTick();
	void CameraMgrRender();
};