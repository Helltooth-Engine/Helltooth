Texture2D shaderTexture;
SamplerState sampleType;

float4 main(float4 position : SV_POSITION, float4 color : COLOR, float2 uvs : UVS) : SV_Target0 {
	return shaderTexture.Sample(sampleType, uvs);
}