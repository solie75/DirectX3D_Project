#pragma once
#include "CScript.h"
class CCameraMoveScript :
    public CScript
{
public:
	CCameraMoveScript();
	~CCameraMoveScript();

	CLONE(CCameraMoveScript);

private:
	float m_fCamSpeed;

public:
	virtual void ScriptTick() override;
};