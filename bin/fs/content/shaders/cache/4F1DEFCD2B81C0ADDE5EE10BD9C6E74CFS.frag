#version 430

layout(std140) uniform Mat
{
    vec4 values[41];
} CBUFFER_1;

struct PS_PUSH_DATA
{
    uint alphaFunc;
    float alphaRef;
    uint needsPremultiply; uint uItemID; int uIsSelected;
};

uniform PS_PUSH_DATA PS_PUSH;

uniform sampler2D tex_map1;
uniform sampler2D tex_map0;

layout(location = 2) in vec4 PARAM_2;
layout(location = 1) in vec4 PARAM_1;
layout(location = 0) in vec4 PARAM_0;
layout(location = 3) in vec4 PARAM_3;
layout(location = 4) in vec4 PARAM_4;
layout(location = 0) out vec4 PIXEL_0;
layout(location = 1) out vec4 PIXEL_1;
layout (location = 2) out uint ItemID;
int stackIdxVar;
int stateVar;
vec4 RVar[128];
vec4 _pixelTmp;
vec4 _pixelTmp_1;

void main()
{
    stackIdxVar = 0;
    stateVar = 0;
    RVar[0u] = PARAM_2;
    RVar[1u] = PARAM_1;
    RVar[2u] = PARAM_0;
    RVar[3u] = PARAM_3;
    RVar[4u] = PARAM_4;
    if (stateVar == 0)
    {
        vec4 _64 = texture(tex_map1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_64.x, _64.y, _64.z, RVar[4u].w);
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
    }
    if (stateVar == 0)
    {
        float _87 = RVar[0u].z;
        float _89 = RVar[4u].z;
        float _92 = (_87 * _89) + uintBitsToFloat(0u);
        float _94 = RVar[0u].y;
        float _96 = RVar[4u].y;
        float _99 = (_94 * _96) + uintBitsToFloat(0u);
        float _101 = RVar[0u].x;
        float _103 = RVar[4u].x;
        float _106 = (_101 * _103) + uintBitsToFloat(0u);
        float _108 = RVar[0u].w;
        RVar[123u].x = _92;
        RVar[123u].y = _99;
        RVar[123u].z = _106;
        RVar[0u].w = uintBitsToFloat(1065353216u);
        float _141 = RVar[2u].z;
        float _143 = RVar[2u].z;
        RVar[127u].x = (CBUFFER_1.values[7].w * ((-_108) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _148 = RVar[3u].x;
        float _151 = (clamp(_106 + uintBitsToFloat(0u), 0.0, 1.0) * _148) + uintBitsToFloat(0u);
        float _153 = RVar[3u].z;
        float _156 = (clamp(_92 + uintBitsToFloat(0u), 0.0, 1.0) * _153) + uintBitsToFloat(0u);
        float _158 = RVar[3u].y;
        float _161 = (clamp(_99 + uintBitsToFloat(0u), 0.0, 1.0) * _158) + uintBitsToFloat(0u);
        float _163 = RVar[2u].y;
        float _165 = RVar[2u].y;
        float _167 = (_163 * _165) + (_141 * _143);
        RVar[123u].x = _151;
        RVar[123u].z = _156;
        RVar[123u].w = _161;
        RVar[122u].x = _167;
        float _175 = clamp(_161 + uintBitsToFloat(0u), 0.0, 1.0);
        float _178 = clamp(_151 + uintBitsToFloat(0u), 0.0, 1.0);
        float _180 = RVar[2u].x;
        float _182 = RVar[2u].x;
        float _184 = (_180 * _182) + _167;
        float _187 = clamp(_156 + uintBitsToFloat(0u), 0.0, 1.0);
        float _189 = RVar[3u].w;
        float _191 = RVar[127u].x;
        RVar[127u].x = _175;
        RVar[127u].y = _178;
        RVar[123u].z = _184;
        RVar[127u].w = _187;
        RVar[3u].w = clamp(_189 + (-_191), 0.0, 1.0);
        float _201 = RVar[1u].x;
        float _205 = RVar[1u].z;
        float _209 = RVar[1u].y;
        float _214 = inversesqrt(_184) * 0.5;
        RVar[126u].x = _214;
        float _224 = RVar[1u].w;
        float _226 = RVar[127u].x;
        float _230 = RVar[1u].w;
        float _232 = RVar[127u].w;
        float _236 = RVar[2u].x;
        RVar[3u].x = ((_201 + (-_178)) * RVar[1u].w) + RVar[127u].y;
        RVar[3u].y = ((_209 + (-_175)) * _224) + _226;
        RVar[3u].z = ((_205 + (-_187)) * _230) + _232;
        RVar[0u].x = (_236 * _214) + uintBitsToFloat(1056964608u);
        float _246 = RVar[2u].y;
        float _248 = RVar[126u].x;
        float _251 = (_246 * _248) + uintBitsToFloat(1056964608u);
        float _253 = RVar[2u].z;
        float _255 = RVar[126u].x;
        float _258 = (_253 * _255) + uintBitsToFloat(1056964608u);
        RVar[0u].y = _251;
        RVar[0u].z = _258;
        float _264 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _251;
        RVar[1u].z = _258;
        RVar[1u].w = _264;
        float _272 = RVar[3u].y;
        float _274 = RVar[3u].z;
        float _276 = RVar[3u].w;
        RVar[0u].x = RVar[3u].x;
        RVar[0u].y = _272;
        RVar[0u].z = _274;
        RVar[0u].w = _276;
    }
    switch (PS_PUSH.alphaFunc & 255u)
    {
        case 0u:
        {
            discard;
        }
        case 1u:
        {
            if (!(RVar[0u].w < PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 2u:
        {
            if (abs(RVar[0u].w - PS_PUSH.alphaRef) > 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 3u:
        {
            if (!(RVar[0u].w <= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 4u:
        {
            if (!(RVar[0u].w > PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 5u:
        {
            if (abs(RVar[0u].w - PS_PUSH.alphaRef) <= 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 6u:
        {
            if (!(RVar[0u].w >= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
    }
    _pixelTmp = RVar[0u];
    uint _352 = PS_PUSH.alphaFunc >> 8u;
    if (_352 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_352 == 2u)
        {
            _pixelTmp = vec4(0.0);
        }
    }
    if ((PS_PUSH.needsPremultiply & 1u) != 0u)
    {
        _pixelTmp *= vec4(_pixelTmp.www, 1.0);
    }
    if (PS_PUSH.uIsSelected != 0) PIXEL_0 = vec4(_pixelTmp.rgb * 0.5f + vec3(1.0f, 0.25f, 0.25f) * 0.5f, _pixelTmp.a); else PIXEL_0 = _pixelTmp; ItemID = PS_PUSH.uItemID;
    _pixelTmp_1 = RVar[1u];
    uint _380 = PS_PUSH.alphaFunc >> 8u;
    if (_380 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_380 == 2u)
        {
            _pixelTmp_1 = vec4(0.0);
        }
    }
    if ((PS_PUSH.needsPremultiply & 2u) != 0u)
    {
        _pixelTmp_1 *= vec4(_pixelTmp_1.www, 1.0);
    }
    PIXEL_1 = _pixelTmp_1;
}

 