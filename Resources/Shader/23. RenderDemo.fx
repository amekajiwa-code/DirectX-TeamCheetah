#include "Global.fx"
#include "Light.fx"
#include "Render.fx"

float4 PS(MeshOutput input) : SV_TARGET
{
	//float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);

	float4 color = DiffuseMap.Sample(LinearSampler, input.uv);

	return color;
}

technique11 T0
{
	PASS_VP(P0, MeshVS, PS)
};
