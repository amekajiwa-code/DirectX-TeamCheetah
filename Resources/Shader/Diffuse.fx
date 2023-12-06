#include "Global.fx"

float3 LightDir; //���� ����
float4 LightDiffuse; //�л걤�� ��
float4 MaterialDiffuse; //�޾� ���� �� �ִ� ���� ���� (0~1)
Texture2D DiffuseMap;

VertexOutput VS(VertexTextureNormal input)
{
	VertexOutput output;
	output.position = mul(input.position, W);
	output.position = mul(output.position, VP);
	output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);

	return output;
}


//Diffuse(�л걤)
/*
��ü�� ǥ�鿡�� �л�Ǿ� ������ ������ ��
�л� �� ������ ���� ��Ⱑ �ٸ�(������Ʈ ����)
*/

float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
    float value = dot(-LightDir, input.normal);
    color = color * value * LightDiffuse * MaterialDiffuse;
	
	return color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};
