#ifndef _PARTICLE_UPDATE
#define _PARTICLE_UPDATE

#include "struct.fx"
#include "func.fx"

RWStructuredBuffer<tParticle> ParticleBuffer : register(u0);
RWStructuredBuffer<int4> ParticleSpawnCount : register(u1);
StructuredBuffer<tParticleModule> ParticleModuleData : register(t20);
Texture2D NoiseTexture : register(t21);

#define ObjectPos g_vec4_0
#define NoiseTexResolution g_vec2_0

#define SpawnCount ParticleSpawnCount[0].x
#define ModuleData ParticleModuleData[0]
#define ParticleMaxCount ParticleModuleData[0].iMaxParticleCount
#define SpawnModule ParticleModuleData[0].Spawn
#define ColorChangeModule PatricleModuleData[0].ColorChange
#define ScaleChangeModule ParticleModuleData[0].ScaleChange

[numThreads(128, 1, 1)]
void CS_ParticleUpdate(int3 _ID : SV_DispatchThreadID)
{
    // if Thread ID over the Max Count of Particle Buffer
    if(ParticleMaxCount <= _ID.x)
    {
        return;
    }
    
    tParticle particle = ParticleBuffer[_ID.x];
    
    if(SpawnModule)
    {
        // if particle was deactivated
        if(particle.Active == 0)
        {
            while(0 < SpawnCount)
            {
                int orgvalue = SpawnCount;
                int outvalue = 0;
                InterlockedCompareExchange(SpawnCount, orgvalue, SpawnCount - 1, outvalue);
                
                if(orgvalue == outvalue)
                {
                    particle.Active = 1;
                    
                    // random value
                    float3 vOut1 = (float3) 0.f;
                    float3 vOut2 = (float3) 0.f;
                    float3 vOut3 = (float3) 0.f;
                 
                    // normalize All valid Thread id between 0 and 1;
                    float fNormalizeThreadID = (float) _ID.x / (float) ParticleMaxCount;
                    GaussianSample(NoiseTexture, NoiseTexResolution, fNormalizeThreadID, vOut1);
                    GaussianSample(NoiseTexture, NoiseTexResolution, fNormalizeThreadID + 0.1f, vOut2);
                    GaussianSample(NoiseTexture, NoiseTexResolution, fNormalizeThreadID + 0.2f, vOut3);
                    
                    // particle Spawn
                    if (ModuleData.SpawnShapeType == 0)
                    {
                        particle.vLocalPos.xyz = float3((ModuleData.vSpawnScaleMax.x / 2.f) * vOut1.r - (ModuleData.vSpawnScaleMax.x / 2.f) * 0.5f
                                                        , (ModuleData.vSpawnScaleMax.y / 2.f) * vOut2.r - (ModuleData.vSpawnScaleMax.y / 2.f) * 0.5f
                                                        , 0.f);

                        particle.vWorldPos.xyz = ObjectPos.xyz + particle.vLocalPos.xyz;
                        
                        // Set Ramdom Scale in SpawnSize Rage (if min and max are same, the scale is fixed)
                        float4 vSpawnScale = ModuleData.vSpawnScaleMin + (ModuleData.vSpawnScaleMax - ModuleData.vSpawnScaleMin) * vOut3.x;
                        
                        particle.vWorldScale.xyz = vSpawnScale.xyz;
                    }

                    // Set Particle Mass;
                    particle.Mass = 1.f;
                    
                    // Add Velocity module
                    if (ModuleData.AddVelocity)
                    {
                        // From Centor
                        if(ModuleData.AddVelocityType == 0)
                        {
                            float3 vVelocity = normalize(particle.vLocalPos.xyz);
                            particle.vVelocity.xyz = vVelocity * ModuleData.Speed;
                        }
                        
                        // To Center
                        else if(ModuleData.AddVelocityType == 1)
                        {
                            float3 vVelocity = -normalize(particle.vLocalPos.xyz);
                            particle.vVelocity.xyz = vVelocity * ModuleData.Speed;
                        }
                        
                        // Fixed Direction
                        else
                        {
                            particle.vVelocity.xyz = normalize(ModuleData.vVelocityDir) * ModuleData.Speed;
                        }
                    }
                    
                    particle.vColor = ModuleData.vSpawnColor;
                    particle.Age = 0.f;
                    particle.LifeTime = ModuleData.MinLifeTime + (ModuleData.MaxLifeTime - ModuleData.MinLifeTime) * vOut2.r;
                    break;
                }
            }
        }
    }
    
    // particle active
    if (particle.Active)
    {
        // Accumulate DeltaTime to Particle Age
        particle.PrevAge = particle.Age;
        particle.Age += g_deltaTime;
        particle.NormalizedAge = saturate(particle.Age / particle.LifeTime);
        particle.vForce.xyz = (float3) 0.f;
        
        // if over the particle LifeTime
        if (particle.LifeTime < particle.Age)
        {
            particle.Active = 0;
        }
        
        // NoiseForce Module (Apply random force to Activated particle
        /*if (ModuleData.NoiseForce)
        {
            if(particle.PrevAge == 0.f)
            {
                float3 vOut1 = (float3) 0.f;
                float3 vOut2 = (float3) 0.f;
                float3 vOut3 = (float3) 0.f;
                
                // Normalize All Valid Thread's ID between 0 and 1;
                float fNormalizeThreadID = (float) _ID.x / (float) ParticleMaxCount;
                GaussianSample(NoiseTexture, NoiseTexResolution, fNormalizeThreadID, vOut1);
                GaussianSample(NoiseTexture, NoiseTexResolution, fNormalizeThreadID + 0.1f, vOut2);
                GaussianSample(NoiseTexture, NoiseTexResolution, fNormalizeThreadID + 0.2f, vOut3);
                
                float3 vForce = normalize(float3(vOut1.x, vOut2.x, vOut1.z) * 2.f - 1.f);
                particle.vRandomForce.xyz = vForce * ModuleData.fNoiseForce;
            }
            else
            {
                int Age = int(particle.Age * (1.f / ModuleData.fNoiseTerm));
                int PrevAge = int(particle.PrevAge * (1.f / ModuleData.fNoiseTerm));

                // Apply new Random Force when 
                // what is age and PrevAge and Normalized Age
                // particle.Age 는 deltaTIme 이 누적된다. 
                // particle.PrevAge 는 이전 Tick 에서의 Age 이다.
                // 어떻게 Age 와 PrevAge 가 같을 수 있지 
            }
            
            particle.vForce.xyz += particle.vRandomForce.xyz;
        }*/

        // if Apply Force to particle, Calculate change of Velocity
        float3 vAccel = particle.vForce.xyz / particle.Mass;
        particle.vVelocity.xyz += vAccel * g_deltaTime;
        
         // Speed Drag Module
        if (ModuleData.Drag)
        {
        // current velocity of particle
            float Speed = length(particle.vVelocity);
            float fDrag = ModuleData.StartDrag + (ModuleData.EndDrag - ModuleData.StartDrag) * particle.NormalizedAge;

        // prevent inversing of Velocity
            if (fDrag <= 0.f)
            {
                fDrag = 0.001f;
            }
            if (fDrag < Speed)
            {
                particle.vVelocity = normalize(particle.vVelocity) * fDrag;
            }
        }
        
        // move particle with velocity
        if (ModuleData.Space == 0)
        {
            particle.vWorldPos += particle.vVelocity * g_deltaTime;
        }
        else if (ModuleData.Space == 1)
        {
            particle.vLocalPos += particle.vVelocity * g_deltaTime;
            particle.vWorldPos.xyz = particle.vLocalPos.xyz + ObjectPos.xyz;
        }
    
        // Change Size Module
        if (ModuleData.ScaleChange)
        {
            particle.ScaleFactor = ModuleData.StartScale + particle.NormalizedAge * (ModuleData.EndScale - ModuleData.StartScale);
        }
        else
        {
            particle.ScaleFactor = 1.f;
        }
    
        // Change color Module
        if (ModuleData.ColorChange)
        {
            particle.vColor = ModuleData.vStartColor + particle.NormalizedAge * (ModuleData.vEndColor - ModuleData.vStartColor);
        }
        
    }
  
    // Apply Change
    ParticleBuffer[_ID.x] = particle;
}

#endif