#include "pch.h"
#include "CScript.h"

CScript::CScript(SCRIPT_TYPE _iScriptType)
	: CComponent(COMPONENT_TYPE::SCRIPT)
	, m_iScriptType(_iScriptType)
{
}

CScript::~CScript()
{
}
