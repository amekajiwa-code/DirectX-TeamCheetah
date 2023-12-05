#include "Global.fx"

float4 LightAmbient; //ȯ�汤�� ����
float4 MaterialAmbient; //ȯ�汤�� �޾Ƶ� �� �� �ִ� ����(0~1)

VertexOutput VS(VertexTextureNormal input)
{
	VertexOutput output;
	output.position = mul(input.position, W);
	output.position = mul(output.position, VP);
	output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);

	return output;
}

Texture2D Texture0;

//Ambient(ȯ�汤/�ֺ���)
//������ �ݻ縦 ���ļ� ������ �Һи��� ��
//������ ���� ������ ǥ��

float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = LightAmbient * MaterialAmbient;
    //return color;
	return Texture0.Sample(LinearSampler, input.uv) * color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};
