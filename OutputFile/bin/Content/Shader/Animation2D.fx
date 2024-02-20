#ifndef _ANIMATION2D
#define _ANIMATION2D

#include "value.fx"

VS_OUT VS_Ani2D(VS_IN _in)
{
    VS_OUT Out = (VS_OUT) 0.0f;

    float4 world = mul(float4(_in.LocalPos, 1.0f), g_matWorld);
    float4 view = mul(world, g_matView);
    float4 proj = mul(view, g_matProj);
    
    Out.Position = proj;
    Out.UV = _in.UV;
    
    return Out;
}

float4 PS_Ani2D(VS_OUT _in) : SV_TARGET
{
    float4 color = (float4) 1.0f;
    
    // Set Texcoord size
    /*float2 modifiedTexcoord = (float2) 0.f;
    if (SpriteNum >= 10)
    {
        modifiedTexcoord.x = _in.UV.x * 0.1f;
        
    }
    else
    {
        modifiedTexcoord.x = _in.UV.x * (1.f / CurSpriteNum);
    }
    
    modifiedTexcoord.y = _in.UV.y * (1.f / ((SpriteNum - 1 / 10) + 1));
    
    // Set Texcoord Offset
    modifiedTexcoord.x += ((CurSpriteNum & 10) * modifiedTexcoord.x);
    modifiedTexcoord.y += (((CurSpriteNum - 1) / 10) * modifiedTexcoord.y);*/
    
    
    ///////
    
    /*
    float2 modifiedTexcoord = _in.UV;
    if (SpriteNum > 9)
    {
        modifiedTexcoord.x *= 0.1f;
        modifiedTexcoord.y *= 1.f / ((SpriteNum - 1 / 10) + 1);

    }
    else
    {
        modifiedTexcoord.x *= (1.f / SpriteNum);
    }*/
    
    float2 modifiedTexcoord = _in.UV;
    modifiedTexcoord.x *= 0.1f;
    //modifiedTexcoord.x += 1.f + CurSpriteNum * modifiedTexcoord.x;
    modifiedTexcoord.x += CurSpriteNum * (0.1);
    
    //modifiedTexcoord.x = _in.UV.x * 0.1f;
    //modifiedTexcoord.x += CurSpriteNum * modifiedTexcoord.x;
    
    
    color = atlasTexture.Sample(g_sam_0, modifiedTexcoord);
	
    return color;
}

#endif

//float2 modifiendTexcoord = In.UV * SpriteSize + Offset;

//sprite.Offset = Vector2(i*(spriteSize.x / width), 0.0f);