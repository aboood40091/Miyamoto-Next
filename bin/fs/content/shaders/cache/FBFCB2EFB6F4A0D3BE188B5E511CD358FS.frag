#version 430

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
        vec4 _60 = texture(tex_map0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[3u] = vec4(_60.x, _60.y, _60.z, RVar[3u].w);
    }
    if (stateVar == 0)
    {
        float _70 = RVar[0u].z;
        float _72 = RVar[3u].z;
        float _75 = (_70 * _72) + uintBitsToFloat(0u);
        float _77 = RVar[0u].y;
        float _79 = RVar[3u].y;
        float _82 = (_77 * _79) + uintBitsToFloat(0u);
        float _84 = RVar[0u].x;
        float _86 = RVar[3u].x;
        float _89 = (_84 * _86) + uintBitsToFloat(0u);
        RVar[123u].x = _75;
        RVar[123u].y = _82;
        RVar[123u].z = _89;
        RVar[3u].w = uintBitsToFloat(0u);
        RVar[0u].w = uintBitsToFloat(1065353216u);
        float _100 = RVar[2u].z;
        float _102 = RVar[2u].z;
        float _113 = clamp(_89 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].y = clamp(_75 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].z = clamp(_82 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].w = _113;
        float _119 = RVar[2u].x;
        float _121 = RVar[2u].y;
        float _126 = RVar[2u].x;
        float _128 = RVar[2u].y;
        float _144 = RVar[1u].z;
        float _146 = RVar[127u].y;
        float _150 = RVar[1u].y;
        float _152 = RVar[127u].z;
        float _157 = inversesqrt(dot(vec4(_119, _121, _100 * _102, uintBitsToFloat(2147483648u)), vec4(_126, _128, uintBitsToFloat(1065353216u), uintBitsToFloat(0u)))) * 0.5;
        RVar[3u].x = ((RVar[1u].x + (-_113)) * RVar[1u].w) + RVar[127u].w;
        RVar[127u].x = _157;
        float _167 = RVar[1u].w;
        float _169 = RVar[127u].z;
        float _173 = RVar[1u].w;
        float _175 = RVar[127u].y;
        float _179 = RVar[2u].y;
        RVar[0u].x = (RVar[2u].x * _157) + uintBitsToFloat(1056964608u);
        RVar[3u].y = ((_150 + (-_152)) * _167) + _169;
        RVar[3u].z = ((_144 + (-_146)) * _173) + _175;
        RVar[0u].y = (_179 * _157) + uintBitsToFloat(1056964608u);
        float _188 = RVar[2u].z;
        float _190 = RVar[127u].x;
        float _193 = (_188 * _190) + uintBitsToFloat(1056964608u);
        RVar[0u].z = _193;
        float _198 = RVar[0u].y;
        float _200 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _198;
        RVar[1u].z = _193;
        RVar[1u].w = _200;
        float _208 = RVar[3u].y;
        float _210 = RVar[3u].z;
        float _212 = RVar[3u].w;
        RVar[0u].x = RVar[3u].x;
        RVar[0u].y = _208;
        RVar[0u].z = _210;
        RVar[0u].w = _212;
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
    uint _288 = PS_PUSH.alphaFunc >> 8u;
    if (_288 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_288 == 2u)
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
    uint _316 = PS_PUSH.alphaFunc >> 8u;
    if (_316 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_316 == 2u)
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