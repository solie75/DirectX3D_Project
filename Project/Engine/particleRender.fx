#ifndef _PARTICLE_RENDER
#define _PARTICLE_RENDER

#include "value.fx"
#include "struct.fx"

// ========================
// Particle Render Shader
// mesh : RectMesh

// Parameter
// g_int_0 : Particle Index
// =========================

StructuredBuffer<tParticle> ParticleBuffer : register(t20);
StructuredBuffer<tParticleModule> ParticleModuleData : register(t21);
#define ModuleData ParticleModuleData[0]

struct VS_In
{
    float3 vPos : POSITION;
    uint iInstID : SV_InstanceID;
};

struct VS_Out
{
    float3 vPos : POSITION;
    uint iInstID : SV_InstanceID;
};

VS_Out VS_ParticleRender(VS_In _in)
{
    VS_Out output = (VS_OUT) 0.f;
    
    output.vPos = _in.vPos;
    output.iInstID = _in.iInstID;
    
    return output;
}

// use Geometry Shader
// 1. control pipeline (Cull UnActivated particle)
// 2. Set Billboard ( Always looking at the camera )
// 3. Rotational Alignment based ConstructGSWithSO speed

struct GS_Out
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    int iInstID : SV_InstanceID;
};

[maxvertexcount(6)]
void GS_ParticleRender(point VS_Out _in[1], inout TriangleStream<GS_Out> _outstream)
{
    uint id = _in[1].iInstID;
    
    if(0 == ParticleBuffer[id].Active)
    {
        return;
    }
    
    float3 vParticleViewPos = mul(float4(ParticleBuffer[id].vWorldPos.xyz, 1.f), g_matView).xyz;
    float2 vParticleScale = ParticleBuffer[id].vWorldScale.xy * ParticleBuffer[id].ScaleFactor;

    // 0 -- 1
    // |    |
    // 3 -- 2
    float3 NewPos[4] =
    {
        float3(-vParticleScale.x / 2.f, +vParticleScale.y / 2.f, 0.f),
        float3(+vParticleScale.x / 2.f, +vParticleScale.y / 2.f, 0.f),
        float3(+vParticleScale.x / 2.f, -vParticleScale.y / 2.f, 0.f),
        float3(-vParticleScale.x / 2.f, -vParticleScale.y / 2.f, 0.f)
    };
    
    if (ModuleData.Render)
    {
        // Apply Scale Changing According Rate of Current Speed / Max Speed
        if(ModuleData.bScaleChangeOnVelocity)
        {
            // figure out Cur Particle's velocity
            float fCurSpeed = length(ParticleBuffer[id].vVelocity); // length() return vec's size
            if (ModuleData.vMaxSpeed < fCurSpeed)
            {
                fCurSpeed = ModuleData.vMaxSpeed;
            }

            // Ratio of Current speed to maximum speed
            float fRatio = saturate(fCurSpeed / ModuleData.vMaxSpeed);
            
            // scale change according to ratio
            float3 fScale = (ModuleData.vMaxScaleChangeOnVelocity.xyz) * fRatio;
            
            for (int i = 0; i < 3; i++)
            {
                if (fScale[i] < 1.f)
                {
                    fScale[i] = 1.f;
                }
            }
            NewPos[0] *= fScale;
            NewPos[3] *= fScale;
        }
        
        // Apply Rotation in Direction of movement
        if(ModuleData.bRotateToMoveDirection)
        {
            // Translate World Space's Velocity to View Space
            float3 vVelocity = normalize(ParticleBuffer[id].vVelocity);
            vVelocity = mul(float4(vVelocity, 0.f), g_matView).xyz;

            // Calculate Angle between Direction of Right(+x) and Direction of Movement
            float3 vRight = float3(1.f, 0.f, 0.f);
            float fTheta = acos(dot(vRight, vVelocity));

            // acos return value between 0 and pi
            // if you want rotate over the pi, (2pi - (return value of acos))
            if (vVelocity.y < vRight.y)
            {
                fTheta = (2.f * 3.1415926535) - fTheta;
            }
            
            // create rotate matrix of Z-axis
            float3x3 matRotZ =
            {
                cos(fTheta), sin(fTheta), 0,
                -sin(fTheta), cos(fTheta), 0,
                          0, 0, 1.f,
            };
            
            // rotate vertex of particle
            for (int i = 0; i < 4; ++i)
            {
                NewPos[i] = mul(NewPos[i], matRotZ);
            }
        }
    }
    
    GS_Out output[4] = { (GS_Out) 0.f, (GS_Out) 0.f, (GS_Out) 0.f, (GS_Out) 0.f };
    
    output[0].vPosition = mul(float4(NewPos[0] + vParticleViewPos, 1.f), g_matProj);
    output[0].vUV = float2(0.f, 0.f);
    output[0].iInstID = id;
    
    output[1].vPosition = mul(float4(NewPos[1] + vParticleViewPos, 1.f), g_matProj);
    output[1].vUV = float2(1.f, 0.f);
    output[1].iInstID = id;
    
    output[2].vPosition = mul(float4(NewPos[2] + vParticleViewPos, 1.f), g_matProj);
    output[2].vUV = float2(1.f, 1.f);
    output[2].iInstID = id;
    
    output[3].vPosition = mul(float4(NewPos[3] + vParticleViewPos, 1.f), g_matProj);
    output[3].vUV = float2(0.f, 1.f);
    output[3].iInstID = id;
    
    // Create Vertex
    _outstream.Append(output[0]);
    _outstream.Append(output[1]);
    _outstream.Append(output[2]);
    _outstream.RestartStrip();
    
    _outstream.Append(output[0]);
    _outstream.Append(output[2]);
    _outstream.Append(output[3]);
    _outstream.RestartStrip();
}

float4 PS_ParticleRender(GS_Out _in) : SV_Target
{
    float4 vOutColor = float4(0.f, 1.f, 0.f, 1.f);
    
    if(g_btex_0)
    {
        vOutColor = g_tex_0.Sample(pointSampler, _in.vUV);
        vOutColor.rgb *= ParticleBuffer[_in.iInstID].vColor.rgb;
    }
    
    return vOutColor;
}
#endif