#pragma once
#include "CSingleton.h"

class CEditObjMgr
	: public CSingleton<CEditObjMgr>
{
public:
	CEditObjMgr();
	~CEditObjMgr();

	SINGLE(CEditObjMgr);

};

