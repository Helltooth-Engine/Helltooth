struct Out {
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

Out main(float2 position : POSITION) {
	Out o;
	float4 pos = float4(position, 0.0, 1.0);
	o.position = pos;
	o.color = pos;
	return o;
}