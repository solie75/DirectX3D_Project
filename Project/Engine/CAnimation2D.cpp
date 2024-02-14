#include "pch.h"
#include "CAnimation2D.h"
//#include <wincodec.h>

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
	std::filesystem::path Path = L"..\\OutputFile\\bin\\Content\\Sprite\\";
	Path += _spriteName + L"\\";
	Path += _spriteName + L"_1.png";
	CTexture* tempTex = new CTexture;
	return tempTex->LoadRes(Path);
}

void CAnimation2D::CreateAtlas(Vec2 _spriteSize, UINT _spriteNum) // ���⿡�� Size �� �׳� �����ͼ� �� ������ ���� �˾Ƴ��� �Ǵ� �� �ƴѰ�?
{
	// �ϴ� Sprite �˻��� �غ���.
	if (S_OK != FindSprite(m_sAni2DName))
	{
		MessageBox(nullptr, L"Sprite �̹����� �����ϴ�.", L"Sprite �̹��� ���� ����", MB_OK);
		return;
	}

	// Sprite �� ���� �Ѵٸ�
	//Ptr<CTexture> tempAtlasTex = new CTexture;
	
	// sprite file path
	std::filesystem::path Path = L"..\\OutputFile\\bin\\Content\\Sprite\\";
	Path += m_sAni2DName + L"\\" + m_sAni2DName; // "������\\���ϸ�"


	//Ptr<ScratchImage> atlasImage;
	Vec2 atlasSize = Vec2(0, 0);
	Vec2 spriteSize = Vec2(0, 0);

	UINT spriteNum = 0;

	CTexture* tempSprite = new CTexture;

	// Count Sprite Num
	for (int i = 0; true; ++i)
	{
		std::filesystem::path SpritePath = Path;
		SpritePath += std::to_wstring(i + 1) + L".png";
		HRESULT hr = tempSprite->LoadRes(SpritePath);
		if (S_OK == hr)
		{
			spriteNum++;
		}
		else
		{
			spriteSize.x = tempSprite->GetScratchImage()->GetMetadata().width;
			spriteSize.y = tempSprite->GetScratchImage()->GetMetadata().height;
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

	// atlas �̹���
	//atlasImage->Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, atlasSize.x, atlasSize.y, 1, 1);
	m_AtlasTex->GetScratchImage()->Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, atlasSize.x, atlasSize.y, 1, 1);

	for (int i = 0; i < spriteNum; ++i)
	{
		std::filesystem::path SpritePath = Path;
		SpritePath += std::to_wstring(i + 1) + L".png";
		tempSprite->LoadRes(SpritePath);

		CopyRectangle(
			*(tempSprite->GetScratchImage()->GetImages()),
			Rect(0, 0, spriteSize.x, spriteSize.y),
			*(m_AtlasTex->GetScratchImage())->GetImages(),
			TEX_FILTER_DEFAULT,
			(spriteNum % 10 - 1) * spriteSize.x,
			((spriteNum - 1) / 10) * spriteSize.y
		);
	}

	SaveAtlas();
}

void CAnimation2D::SaveAtlas()
{
	const wstring& AtlasPath = L"..\\OutputFile\\bin\\Content\\Atlas\\" + m_sAni2DName + L".png";
	HRESULT hr = SaveToWICFile(
		*(m_AtlasTex->GetScratchImage()->GetImages()),
		//m_AtlasTex->GetScratchImage()->GetImageCount(),  
		WIC_FLAGS_NONE,
		GetWICCodec(WIC_CODEC_PNG),
		AtlasPath.c_str()
	);

	if (S_OK != hr)
	{
		MessageBox(nullptr, L"SaveToWICFile ����", L"SaveAtlas", MB_OK);
	}
}