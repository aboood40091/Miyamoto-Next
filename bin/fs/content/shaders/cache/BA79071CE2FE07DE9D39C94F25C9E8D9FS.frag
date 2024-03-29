#version 430

struct PS_PUSH_DATA
{
    uint alphaFunc;
    float alphaRef;
    uint needsPremultiply; uint uItemID; int uIsSelected;
};

uniform PS_PUSH_DATA PS_PUSH;

uniform sampler2D cTexMap0;

layout(location = 0) in vec4 PARAM_0;
layout(location = 1) in vec4 PARAM_1;
layout(location = 2) in vec4 PARAM_2;
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
    RVar[0u] = PARAM_0;
    RVar[1u] = PARAM_1;
    RVar[2u] = PARAM_2;
    RVar[3u] = PARAM_3;
    if (stateVar == 0)
    {
        RVar[3u] = texture(cTexMap0, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
    }
    if (stateVar == 0)
    {
        float _68 = RVar[2u].x;
        float _70 = RVar[2u].y;
        float _72 = RVar[2u].z;
        float _77 = RVar[2u].x;
        float _79 = RVar[2u].y;
        float _81 = RVar[2u].z;
        float _86 = RVar[0u].x;
        float _88 = RVar[3u].x;
        float _89 = _86 * _88;
        RVar[127u].w = _89;
        float _97 = RVar[0u].z;
        float _99 = RVar[3u].z;
        float _100 = _97 * _99;
        float _102 = RVar[0u].y;
        float _104 = RVar[3u].y;
        float _105 = _102 * _104;
        float _107 = RVar[0u].w;
        float _109 = RVar[3u].w;
        float _112 = inversesqrt(dot(vec4(_68, _70, _72, uintBitsToFloat(2147483648u)), vec4(_77, _79, _81, uintBitsToFloat(0u))));
        RVar[127u].x = RVar[1u].x + (-_89);
        RVar[127u].y = _100;
        RVar[127u].z = _105;
        RVar[0u].w = _107 * _109;
        float _118 = RVar[2u].x;
        float _119 = _118 * _112;
        float _121 = RVar[2u].y;
        float _122 = _121 * _112;
        float _124 = RVar[2u].z;
        float _125 = _124 * _112;
        float _127 = RVar[1u].y;
        float _131 = RVar[1u].z;
        RVar[126u].x = _119;
        RVar[126u].y = _122;
        RVar[125u].z = _125;
        RVar[126u].w = _127 + (-_105);
        RVar[126u].z = _131 + (-_100);
        RVar[0u].x = (RVar[127u].x * RVar[1u].w) + RVar[127u].w;
        float _164 = RVar[126u].z;
        float _166 = RVar[1u].w;
        float _168 = RVar[127u].y;
        float _175 = inversesqrt(dot(vec4(_119, _122, _125, uintBitsToFloat(2147483648u)), vec4(_119, _122, _125, uintBitsToFloat(0u)))) * 0.5;
        RVar[0u].y = (RVar[126u].w * RVar[1u].w) + RVar[127u].z;
        RVar[0u].z = (_164 * _166) + _168;
        RVar[1u].w = uintBitsToFloat(1065353216u);
        float _180 = RVar[126u].x;
        float _184 = (_180 * _175) + uintBitsToFloat(1056964608u);
        float _186 = RVar[126u].y;
        float _189 = (_186 * _175) + uintBitsToFloat(1056964608u);
        float _191 = RVar[125u].z;
        float _194 = (_191 * _175) + uintBitsToFloat(1056964608u);
        RVar[1u].x = _184;
        RVar[1u].y = _189;
        RVar[1u].z = _194;
        float _199 = RVar[1u].w;
        RVar[2u].x = _184;
        RVar[2u].y = _189;
        RVar[2u].z = _194;
        RVar[2u].w = _199;
        float _207 = RVar[0u].y;
        float _209 = RVar[0u].z;
        float _211 = RVar[0u].w;
        RVar[1u].x = RVar[0u].x;
        RVar[1u].y = _207;
        RVar[1u].z = _209;
        RVar[1u].w = _211;
    }
    switch (PS_PUSH.alphaFunc & 255u)
    {
        case 0u:
        {
            discard;
        }
        case 1u:
        {
            if (!(RVar[1u].w < PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 2u:
        {
            if (abs(RVar[1u].w - PS_PUSH.alphaRef) > 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 3u:
        {
            if (!(RVar[1u].w <= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 4u:
        {
            if (!(RVar[1u].w > PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 5u:
        {
            if (abs(RVar[1u].w - PS_PUSH.alphaRef) <= 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 6u:
        {
            if (!(RVar[1u].w >= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
    }
    _pixelTmp = RVar[1u];
    uint _287 = PS_PUSH.alphaFunc >> 8u;
    if (_287 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_287 == 2u)
        {
            _pixelTmp = vec4(0.0);
        }
    }
    if ((PS_PUSH.needsPremultiply & 1u) != 0u)
    {
        _pixelTmp *= vec4(_pixelTmp.www, 1.0);
    }
    if (PS_PUSH.uIsSelected != 0) PIXEL_0 = vec4(_pixelTmp.rgb * 0.5f + vec3(1.0f, 0.25f, 0.25f) * 0.5f, _pixelTmp.a); else PIXEL_0 = _pixelTmp; ItemID = PS_PUSH.uItemID;
    _pixelTmp_1 = RVar[2u];
    uint _315 = PS_PUSH.alphaFunc >> 8u;
    if (_315 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_315 == 2u)
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