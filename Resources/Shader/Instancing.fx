#include "Global.fx"
#include "Light.fx"
#include "Render.fx"

Texture2D dissolve;
float time;

float4 DefaultPS(MeshOutput input) : SV_TARGET
{
    ComputeNormalMapping(input.normal, input.tangent, input.uv);
    float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);

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

float4 PS_RED(MeshOutput input) : SV_TARGET
{
    return float4(1, 0, 0, 1);
}

technique11 T0
{
    //Mesh
	PASS_VP(P0, MeshVS, DefaultPS)
    //Model Static
    PASS_VP(P1, StaticModelVS, DefaultPS)
    //Model Dynamic
    PASS_VP(P2, DynamicModelVS, DefaultPS)
};
