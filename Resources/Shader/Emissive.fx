#include "Global.fx"

Texture2D DiffuseMap;
float4 MaterialEmissive;

MeshOutput VS(VertexTextureNormal input)
{
	MeshOutput output;
	output.position = mul(input.position, W);
    output.worldPosition = input.position;
	output.position = mul(output.position, VP);
	

    output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);

	return output;
}

//Emissive(�ܰ���)
/*
�ܰ����� ���� �� ����Ѵ�(������Ʈ)
*/

float4 PS(MeshOutput input) : SV_TARGET
{
    float3 cameraPosition = -V._41_42_43;
    float3 E = normalize(cameraPosition - input.worldPosition);
	
    float value = saturate(dot(E, input.normal));
    float emissive = 1.0f - value;
	//min max x
    emissive = smoothstep(0.0f, 1.0f, emissive);
    emissive = pow(emissive, 5);
	
    float4 texColor = DiffuseMap.Sample(LinearSampler, input.uv);
    float4 color = lerp(texColor, MaterialEmissive, emissive);
	
	return color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};
