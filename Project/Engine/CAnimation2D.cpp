#include "pch.h"
#include "CAnimation2D.h"
#include "CPathMgr.h"

CAnimation2D::CAnimation2D(const wstring _ani2DName)
	: m_AtlasTex(nullptr)
	, m_pOwner(nullptr)
	, m_fDurationPerSprite(0.f)
	, m_bLoop(false)
	, m_bLoopFinish(false)
	, m_iCurSpriteNum(0)
	, m_sAni2DName(_ani2DName)
{
	m_AtlasTex = new CTexture;
}

CAnimation2D::~CAnimation2D()
{
}

HRESULT CAnimation2D::FindAtlas(const wstring _atlasName)
{
	std::filesystem::path Path = L"..\\OutputFile\\bin\\Content\\Atlas\\";
	Path += _atlasName + L"\\";
	Path += _atlasName;
	Path += L".png";
	
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

void CAnimation2D::CreateAtlas(Vec2 _spriteSize, UINT _spriteNum) // 여기에서 Size 도 그냥 가져와서 그 데이터 에서 알아내면 되는 것 아닌가?
{
	// 일단 Sprite 검색을 해보자.
	if (S_OK != FindSprite(m_sAni2DName))
	{
		MessageBox(nullptr, L"Sprite 이미지가 없습니다.", L"Sprite 이미지 존재 여부", MB_OK);
		return;
	}

	// Sprite 가 존재 한다면
	//Ptr<CTexture> tempAtlasTex = new CTexture;
	
	// sprite file path
	std::filesystem::path Path = CPathMgr::GetInst()->GetContentPath();
	Path += L"Sprite\\" + m_sAni2DName + L"\\" + m_sAni2DName; // "폴더명\\파일명"
	//Path += m_sAni2DName + L"\\" + m_sAni2DName; 

	//Ptr<ScratchImage> atlasImage;
	Vec2 atlasSize = Vec2(0, 0);
	Vec2 spriteSize = Vec2(0, 0);

	UINT spriteNum = 0;

	CTexture* tempSprite = new CTexture;

	// Count Sprite Num
	for (int i = 0; true; ++i)
	{
		std::filesystem::path SpritePath = Path;
		SpritePath += L"_" + std::to_wstring(i + 1) + L".png";
		HRESULT hr = tempSprite->LoadRes(SpritePath);
		if (S_OK == hr)
		{
			spriteNum++;
			spriteSize.x = tempSprite->GetScratchImage()->GetMetadata().width;
			spriteSize.y = tempSprite->GetScratchImage()->GetMetadata().height;
		}
		else
		{
			break;
		}
	}

	// Calculate Atlas Size
	if (spriteNum > 9)
	{
		atlasSize.x = spriteSize.x * 10;
	}
	else
	{
		atlasSize.x = spriteSize.x * spriteNum;
	}
	atlasSize.y = spriteSize.y * ((spriteNum-1)/ 10 + 1);

	// atlas 이미지
	// atlas scratch image init
	m_AtlasTex->GetScratchImage()->Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, atlasSize.x, atlasSize.y, 1, 1);

	for (int i = 0; i < spriteNum; ++i)
	{
		std::filesystem::path SpritePath = Path;
		SpritePath += L"_" + std::to_wstring(i + 1) + L".png";
		tempSprite->LoadRes(SpritePath);

		CopyRectangle(
			*(tempSprite->GetScratchImage()->GetImages()),
			Rect(0, 0, spriteSize.x, spriteSize.y),
			*(m_AtlasTex->GetScratchImage())->GetImages(),
			TEX_FILTER_DEFAULT,
			(i % 10) * spriteSize.x, // 여기를 다시 생각해 볼것
			((i - 1) / 10) * spriteSize.y
		);
	}

	SaveAtlas();
}

void CAnimation2D::SaveAtlas()
{
	std::filesystem::path AtlasPath = CPathMgr::GetInst()->GetContentPath();
	AtlasPath += L"Atlas\\" + m_sAni2DName + L".png";
	HRESULT hr = SaveToWICFile(
		*(m_AtlasTex->GetScratchImage()->GetImages()),
		//m_AtlasTex->GetScratchImage()->GetImageCount(),  
		WIC_FLAGS_NONE,
		GetWICCodec(WIC_CODEC_PNG),
		AtlasPath.c_str()
	);

	if (S_OK != hr)
	{
		MessageBox(nullptr, L"SaveToWICFile 실패", L"SaveAtlas", MB_OK);
	}
}