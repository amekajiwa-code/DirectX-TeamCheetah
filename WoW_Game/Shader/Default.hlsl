struct VS_INPUT
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};
//vs
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = input.position;
    output.color = input.color;
    
    return output;
}
//ps
float4 PS(VS_OUTPUT input) : SV_Target
{
    //float4 color = { 1, 0, 0, 0 };
    
    return input.color;
}