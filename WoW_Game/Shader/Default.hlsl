struct VS_INPUT
{
    float4 position : POSITION;
    //float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    //float4 color : COLOR;
    float2 uv : TEXCOORD;   
};

cbuffer TransformData : register(b0)
{
    float4 offset; 
}

//vs
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = input.position + offset;
    //output.color = input.color;
    output.uv = input.uv;
    
    return output;
}

Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

float4 PS(VS_OUTPUT input) : SV_Target
{
    //float4 color = { 1, 0, 0, 0 };
    
    float4 color = texture0.Sample(sampler0, input.uv);
    
    return color;
}