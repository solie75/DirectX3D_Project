#include "pch.h"
#include "CAnimation2D.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CDevice.h"

CAnimation2D::CAnimation2D(const wstring _ani2DName)
	: m_AtlasTex(nullptr)
	, m_pOwner(nullptr)
	, m_fDurationPerSprite(0.f)
	, m_bLoop(false)
	, m_bLoopFinish(false)
	//, m_iCurSpriteNum(0)
	, m_sAni2DName(_ani2DName)
	, m_fAccumulateTime(0.f)
	//, m_SpriteSize(Vec2(0.f, 0.f))
	, m_tAniCB{}
{
	m_AtlasTex = new CTexture;
}

CAnimation2D::~CAnimation2D()
{
}

HRESULT CAnimation2D::FindAtlas(const wstring _atlasName)
{
	std::filesystem::path Path = CPathMgr::GetInst()->GetContentPath();
	Path += L"Atlas\\" + _atlasName + L".png";

	if (S_OK == m_AtlasTex->LoadRes(Path))
	{
		//m_tAniCB.SpriteNum = m_AtlasTex->GetScratchImage()->GetMetadata().width();
		m_tAniCB.SpriteNum = 10;
		m_fDurationPerSprite = 0.1f;
	}

	return m_AtlasTex->LoadRes(Path);
}

HRESULT CAnimation2D::FindSprite(const wstring _spriteName)
{
	std::filesystem::path Path = CPathMgr::GetInst()->GetContentPath(); 
	Path += L"Sprite\\" + _spriteName + L"\\" + _spriteName + L"_1.png";
	/*Path += _spriteName + L"\\";
	Path += _spriteName + L"_1.png";*/
	CTexture* tempTex = new CTexture;
	return tempTex->LoadRes(Path);
}

void CAnimation2D::CreateAtlas(Vec2 _spriteSize, UINT _spriteNum, float _durationTime) // 여기에서 Size 도 그냥 가져와서 그 데이터 에서 알아내면 되는 것 아닌가?
{
	// Set Duration Time
	m_fDurationPerSprite = _durationTime;

	// Find Sprite
	if (S_OK != FindSprite(m_sAni2DName))
	{
		MessageBox(nullptr, L"Sprite 이미지가 없습니다.", L"Sprite 이미지 존재 여부", MB_OK);
		return;
	}

	// sprite file path
	std::filesystem::path Path = CPathMgr::GetInst()->GetContentPath();
	Path += L"Sprite\\" + m_sAni2DName + L"\\" + m_sAni2DName; // "폴더명\\파일명"

	Vec2 atlasSize = Vec2(0, 0);
	UINT spriteNum = 0;

	CTexture* tempSprite = new CTexture;

	// temp Sprite Size
	Vec2 tempSpriteSize = Vec2(0.f, 0.f);

	// Count Sprite Num
	for (int i = 0; true; ++i)
	{
		std::filesystem::path SpritePath = Path;
		SpritePath += L"_" + std::to_wstring(i + 1) + L".png";
		HRESULT hr = tempSprite->LoadRes(SpritePath);
		if (S_OK == hr)
		{
			spriteNum++;
			tempSpriteSize.x = tempSprite->GetScratchImage()->GetMetadata().width;
			tempSpriteSize.y = tempSprite->GetScratchImage()->GetMetadata().height;
		}
		else
		{
			break;
		}
	}

	m_tAniCB.SpriteNum = spriteNum;

	// Calculate Atlas Size
	if (spriteNum > 9)
	{
		atlasSize.x = tempSpriteSize.x * 10;
	}
	else
	{
		atlasSize.x = tempSpriteSize.x * spriteNum;
	}
	atlasSize.y = tempSpriteSize.y * ((spriteNum-1)/ 10 + 1);

	// Init atlas scratch image
	m_AtlasTex->GetScratchImage()->Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, atlasSize.x, atlasSize.y, 1, 1);

	for (int i = 0; i < spriteNum; ++i)
	{
		std::filesystem::path SpritePath = Path;
		SpritePath += L"_" + std::to_wstring(i + 1) + L".png";
		tempSprite->LoadRes(SpritePath);

		CopyRectangle(
			*(tempSprite->GetScratchImage()->GetImages()),
			Rect(0, 0, tempSpriteSize.x, tempSpriteSize.y),
			*(m_AtlasTex->GetScratchImage())->GetImages(),
			TEX_FILTER_DEFAULT,
			(i % 10) * tempSpriteSize.x,
			(i / 10) * tempSpriteSize.y
		);
	}

	// Save
	SaveAtlas();

	// Create SRV
	m_AtlasTex->CreateSRV();
}

void CAnimation2D::SaveAtlas()
{
	// Atlas 폴더에 atlas 저장
	std::filesystem::path AtlasPath = CPathMgr::GetInst()->GetContentPath();
	AtlasPath += L"Atlas\\" + m_sAni2DName + L".png";
	HRESULT hr = SaveToWICFile(
		*(m_AtlasTex->GetScratchImage()->GetImages()),  
		WIC_FLAGS_NONE,
		GetWICCodec(WIC_CODEC_PNG),
		AtlasPath.c_str()
	);

	if (S_OK != hr)
	{
		MessageBox(nullptr, L"SaveToWICFile 실패", L"SaveAtlas", MB_OK);
	}
}

void CAnimation2D::LoadAtlas(const wstring& _atlasName)
{
	std::filesystem::path Path = CPathMgr::GetInst()->GetContentPath();
	Path += L"Atlas\\" + _atlasName + L".png";
	m_AtlasTex->LoadRes(Path);
}

void CAnimation2D::LoadAnimationData(const wstring& _aniName)
{
	std::filesystem::path Path = CPathMgr::GetInst()->GetContentPath();
	Path += L"Data\\AnimationData.json";

	std::wifstream DataFile(Path);

	// 해당 파일이 존재하는 경우
	if (DataFile.is_open())
	{
		std::wstring line;
		//std::wstring tempAniName = L"\"" + _aniName + L"\":";
		while (true)
		{
			std::getline(DataFile, line);
			if (line.find(_aniName) != std::string::npos)
			{
				while (true)
				{
					std::getline(DataFile, line);
					if (line.find(L"spriteNumber") != std::string::npos)
					{
						break;
					}
				}

				//if (line.find(L"\"spriteNumber\": ") != std::string::npos)
				if (line.find(L"spriteNumber") != std::string::npos)
				{
					size_t startPos = line.find(L"[") + 1;
					size_t endPos = line.find(L"]");
					std::wstring numStr = line.substr(startPos, endPos - startPos);

					swscanf_s(numStr.c_str(), L"%d", &(m_tAniCB.SpriteNum));
				}
				std::getline(DataFile, line);
				if(line.find(L"renderingMode") != std::string::npos)
				{

				}
				std::getline(DataFile, line);
				if (line.find(L"spriteSize") != std::string::npos)
				{

				}
				std::getline(DataFile, line);
				if (line.find(L"durationTime") != std::string::npos)
				{
					size_t startPos = line.find(L"[") + 1;
					size_t endPos = line.find(L"]");
					std::wstring numStr = line.substr(startPos, endPos - startPos);

					int tempNum = 0;
					swscanf_s(numStr.c_str(), L"%d", &(tempNum));
					m_fDurationPerSprite = tempNum * 1.f;


					return;
				}
			
			}
		}
	}
}

void CAnimation2D::Ani2DUpdate()
{

}

void CAnimation2D::Ani2DLateUpdate()
{
	// Animation
	m_fAccumulateTime += CTimeMgr::GetInst()->GetDeltaTime();

	if (m_fAccumulateTime > m_fDurationPerSprite)
	{
		// 마지막 sprite 가 유지 시간이 다 된 경우 처음 sprite 로 되돌아 간다.
		if (m_tAniCB.CurSpriteNum == m_tAniCB.SpriteNum -1)
		{
			m_tAniCB.CurSpriteNum = 0;
		}
		else
		{
			m_tAniCB.CurSpriteNum++;
		}

		m_fAccumulateTime = 0.f;
	}

	Ani2DBind();
}

void CAnimation2D::Ani2DBind()
{
	m_AtlasTex->UpdateTexData(12);

	CConstBuffer* tempAni2DCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::ANIMATION2D);
	tempAni2DCB->SetCBData(&m_tAniCB);
	tempAni2DCB->UpdateCBData();
}

Ptr<CTexture> CAnimation2D::GetAtlasTex()
{
	return m_AtlasTex;
}

void CAnimation2D::SetBoolLoop(bool _b)
{
	m_bLoop = _b;
}
