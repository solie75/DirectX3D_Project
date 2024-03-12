#include "pch.h"
#include "CEditObjMgr.h"

void SetDebugRect(const Matrix& _matWorld, Vec4 _vColor, float _fTime)
{
	tDebugShapeInfo info = {};

	info.matWorld = _matWorld;
	info.eShape = SHAPE_TYPE::RECT;
	info.vColor = _vColor;

	CEditObjMgr::GetInst()->AddDebugShapeInfo(info);
}

void SetDebugCircle(const Matrix& _matWorld, Vec4 _vColor, float _fTime)
{
	tDebugShapeInfo info = {};

	info.matWorld = _matWorld;
	info.eShape = SHAPE_TYPE::RECT;
	info.vColor = _vColor;

	CEditObjMgr::GetInst()->AddDebugShapeInfo(info);
}
