struct VS_INPUT
{
	float4 position: POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};


cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_projection;

	unsigned int m_time;
};



VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//output.position = lerp(input.position, input.position1, (float)((sin((float)(m_time / (float)1000.0f)) + 1.0f) / 2.0f));
	
	//World space
	output.position = mul(input.position, m_world);

	//view space
	output.position = mul(output.position, m_view);

	//projection space
	output.position = mul(output.position, m_projection);
	
	
	output.color = input.color;
	output.color1 = input.color1;
	return output;
}