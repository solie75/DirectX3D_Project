#pragma once

#include "CMesh.h"
#include "CShader.h"
#include "CGameObject.h"
//#include "CConstBuffer.h"

//struct tConstantBuffer
//{
//	ComPtr<ID3D11Buffer> mCBBuffer;
//	D3D11_BUFFER_DESC mCBDesc;
//	CB_TYPE eType;
//};

class CEngine
	: public CSingleton<CEngine>
{
	SINGLE(CEngine)

private:
	HWND m_hWnd;

	Vec2 m_vResolution;

	//Vec2 m_vPosition;

	//CConstBuffer* CB;

	//float m_MovingDist;

	CGameObject* m_pGameObj;
public:
	Vec2 GetWindowResolution() { return m_vResolution; }
	HWND GetMainWindowHandle() { return m_hWnd; }
	
public:
	int EngineInit(HWND _hWnd, UINT _iWidth, UINT _iHeight);
	void EngineProgress();

	//void CreateMesh();

	//void SetPosition(Vec2 _pos);
	//void MovePosition();

private:
	void EngineTick();
	void EngineRender();
};


