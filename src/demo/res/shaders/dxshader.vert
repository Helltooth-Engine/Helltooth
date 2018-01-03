struct Out {
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

cbuffer Vertex : register(b0) {
	float4x4 c_projectionMatrix;
	float4x4 c_modelMatrix;
}

Out main(float3 position : POSITION) {
	Out o;
	o.position = mul(c_projectionMatrix, mul(c_modelMatrix, float4(position, 1.0)));
	//o.position = float4(position, 1.0);
	o.color = o.position;
	return o;
}