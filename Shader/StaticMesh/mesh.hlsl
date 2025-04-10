
struct Constant{
    float4x4 worldViewProj;
    float4x4 world;
    float4x4 viewProj;
};

struct Vertex{
    float4 pos : POSITION;
    float4 col : COLOR;
};

struct Pixel{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
};

Constant cb : register(b0);

Pixel main(Vertex v){
    Pixel p;
    p.pos = mul(v.pos, cb.worldViewProj);
    p.col = v.col;
    return p;
}

float4 main(Pixel p) : SV_TARGET{
    float4 c = tex.Sample(sam, p.pos.xy);
    return c;
}