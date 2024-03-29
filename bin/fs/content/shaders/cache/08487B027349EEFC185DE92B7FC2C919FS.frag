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

uniform sampler2D tex_map0;

layout(location = 2) in vec4 PARAM_2;
layout(location = 0) in vec4 PARAM_0;
layout(location = 1) in vec4 PARAM_1;
layout(location = 3) in vec4 PARAM_3;
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
    RVar[1u] = PARAM_0;
    RVar[2u] = PARAM_1;
    RVar[3u] = PARAM_3;
    if (stateVar == 0)
    {
        RVar[3u] = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
    }
    if (stateVar == 0)
    {
        float _68 = RVar[0u].w;
        float _70 = RVar[3u].w;
        float _73 = (_68 * _70) + uintBitsToFloat(0u);
        float _83 = RVar[3u].z;
        float _86 = (CBUFFER_1.values[4].z * _83) + uintBitsToFloat(0u);
        float _90 = RVar[3u].y;
        float _93 = (CBUFFER_1.values[4].y * _90) + uintBitsToFloat(0u);
        float _97 = RVar[3u].x;
        float _100 = (CBUFFER_1.values[4].x * _97) + uintBitsToFloat(0u);
        RVar[123u].x = _73;
        RVar[123u].y = _86;
        RVar[123u].z = _93;
        RVar[123u].w = _100;
        RVar[0u].w = uintBitsToFloat(1065353216u);
        float _112 = clamp(_100 + uintBitsToFloat(0u), 0.0, 1.0);
        float _114 = RVar[2u].z;
        float _116 = RVar[2u].z;
        RVar[127u].x = _112;
        RVar[127u].z = clamp(_86 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].w = clamp(_93 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[3u].w = clamp(_73 + uintBitsToFloat(0u), 0.0, 1.0);
        float _133 = RVar[2u].x;
        float _135 = RVar[2u].y;
        float _140 = RVar[2u].x;
        float _142 = RVar[2u].y;
        float _158 = RVar[1u].z;
        float _160 = RVar[127u].z;
        float _164 = RVar[1u].y;
        float _166 = RVar[127u].w;
        float _171 = inversesqrt(dot(vec4(_133, _135, _114 * _116, uintBitsToFloat(2147483648u)), vec4(_140, _142, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) * 0.5;
        RVar[3u].x = ((RVar[1u].x + (-_112)) * RVar[1u].w) + RVar[127u].x;
        RVar[127u].x = _171;
        float _181 = RVar[1u].w;
        float _183 = RVar[127u].w;
        float _187 = RVar[1u].w;
        float _189 = RVar[127u].z;
        float _193 = RVar[2u].y;
        RVar[0u].x = (RVar[2u].x * _171) + uintBitsToFloat(1056964608u);
        RVar[3u].y = ((_164 + (-_166)) * _181) + _183;
        RVar[3u].z = ((_158 + (-_160)) * _187) + _189;
        RVar[0u].y = (_193 * _171) + uintBitsToFloat(1056964608u);
        float _202 = RVar[2u].z;
        float _204 = RVar[127u].x;
        float _207 = (_202 * _204) + uintBitsToFloat(1056964608u);
        RVar[0u].z = _207;
        float _212 = RVar[0u].y;
        float _214 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _212;
        RVar[1u].z = _207;
        RVar[1u].w = _214;
        float _222 = RVar[3u].y;
        float _224 = RVar[3u].z;
        float _226 = RVar[3u].w;
        RVar[0u].x = RVar[3u].x;
        RVar[0u].y = _222;
        RVar[0u].z = _224;
        RVar[0u].w = _226;
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
    uint _302 = PS_PUSH.alphaFunc >> 8u;
    if (_302 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_302 == 2u)
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
    uint _330 = PS_PUSH.alphaFunc >> 8u;
    if (_330 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_330 == 2u)
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