float4 main(float4 position : SV_POSITION, float4 color : COLOR) : SV_Target0 {
	return float4(color.x + 0.5, color.y + 0.5, color.z + 0.5, color.w);
}