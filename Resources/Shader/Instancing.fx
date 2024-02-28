#include "Global.fx"
#include "Light.fx"
#include "Render.fx"

Texture2D dissolve;
float time;

float4 DefaultPS(MeshOutput input) : SV_TARGET
{
    ComputeNormalMapping(input.normal, input.tangent, input.uv);
    float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
//    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);

    return color;
}

float4 DissolvePS(MeshOutput input) : SV_TARGET
{
    ComputeNormalMapping(input.normal, input.tangent, input.uv);
    float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
 
    float dissolveValue = dissolve.Sample(PointSampler, input.uv).r;
    dissolveValue = saturate(dissolveValue);
    
    float isVisible = dissolveValue - time;
    clip(isVisible);

    return color;
}

Texture2D DepthMap;
float4 PSSHADOW(ShadowOutput input) : SV_TARGET
{
    ComputeNormalMapping(input.normal, input.tangent, input.uv);
    float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
	{
        float LightAmount = 1.0f;
        float4 vPosLight = input.texShadow;
		
        for (int iLight = 0; iLight < 1; iLight++)
        {
	//transform from RT space to texture space.
            float2 ShadowTexC = vPosLight.xy / vPosLight.w;
	// transform to texel space
            float2 texelpos = SMAP_SIZE * ShadowTexC;
	 // Determine the lerp amounts           
            float2 lerps = frac(texelpos);
	 //read in bilerp stamp, doing the shadow checks
            float sourcevals[4];
            sourcevals[0] = (DepthMap.Sample(ShadowSampler, ShadowTexC)
	+ SHADOW_EPSILON < vPosLight.z / vPosLight.w) ? 0.0f : 1.0f;
            sourcevals[1] = (DepthMap.Sample(ShadowSampler, ShadowTexC
	+ float2(1.0 / SMAP_SIZE, 0)) + SHADOW_EPSILON < vPosLight.z / vPosLight.w) ? 0.0f : 1.0f;
            sourcevals[2] = (DepthMap.Sample(ShadowSampler, ShadowTexC
	+ float2(0, 1.0 / SMAP_SIZE)) + SHADOW_EPSILON < vPosLight.z / vPosLight.w) ? 0.0f : 1.0f;
            sourcevals[3] = (DepthMap.Sample(ShadowSampler, ShadowTexC
	+ float2(1.0 / SMAP_SIZE, 1.0 / SMAP_SIZE)) + SHADOW_EPSILON < vPosLight.z / vPosLight.w) ? 0.0f : 1.0f;
	// lerp between the shadow values to calculate our light amount
            LightAmount = lerp(lerp(sourcevals[0], sourcevals[1], lerps.x),
	lerp(sourcevals[2], sourcevals[3], lerps.x),
	 lerps.y);
        }
        float4 finalColor = color * max(0.5f, LightAmount);
        return finalColor;
    }
}

float4 PS_RED(MeshOutput input) : SV_TARGET
{
    return float4(1, 0, 0, 1);
}

float4 PSG(ShadowDepthOutPut input) : SV_TARGET
{
    float shadow = input.d.x / input.d.y;
    return float4(shadow, shadow, shadow, 1.0f);
}


technique11 T0
{
    //Mesh
	PASS_VP(P0, MeshVS, DefaultPS)
    //Model Static
//    PASS_VP(P1, StaticModelVS, DefaultPS)
    PASS_RS_SP(P1, CullNone, StaticModelVS, DefaultPS)
    //Model Dynamic
    PASS_VP(P2, DynamicModelVS, DefaultPS)
    //StaticMesh
	PASS_VP(P3, StaticMeshSHADOW, PSSHADOW)
    //SkeletalMesh
    PASS_VP(P4, SkeletalMeshSHADOW, PSSHADOW)
    //Terrain
    PASS_RS_SP(P5, ShadowRaster, SHADOW_VSSTATIC, PSG)
    PASS_RS_SP(P6, ShadowRaster, SHADOW_VSSKELETAL, PSG)
    //Dissolve Shader
    PASS_VP(P7, DynamicModelVS, DissolvePS)
};
