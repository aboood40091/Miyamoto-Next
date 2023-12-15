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
uniform sampler2D tex_map2;
uniform sampler2D tex_map0;
uniform sampler2D tex_map3;

layout(location = 2) in vec4 PARAM_2;
layout(location = 0) in vec4 PARAM_0;
layout(location = 1) in vec4 PARAM_1;
layout(location = 3) in vec4 PARAM_3;
layout(location = 4) in vec4 PARAM_4;
layout(location = 5) in vec4 PARAM_5;
layout(location = 6) in vec4 PARAM_6;
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
    RVar[4u] = PARAM_4;
    RVar[5u] = PARAM_5;
    RVar[6u] = PARAM_6;
    if (stateVar == 0)
    {
        vec4 _72 = texture(tex_map1, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_72.x, RVar[4u].y, RVar[4u].z, _72.w);
        RVar[9u] = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
    }
    if (stateVar == 0)
    {
        float _96 = RVar[9u].x;
        float _103 = RVar[4u].w;
        float _107 = _103 + (-uintBitsToFloat(1056964608u));
        float _109 = RVar[4u].x;
        float _114 = RVar[9u].y;
        RVar[5u].y = uintBitsToFloat(0u);
        RVar[0u].w = _109 + (-uintBitsToFloat(1056964608u));
        float _139 = RVar[9u].z;
        RVar[4u].x = _107 * CBUFFER_1.values[11].y;
        RVar[4u].y = _107 * CBUFFER_1.values[11].x;
        RVar[3u].z = (CBUFFER_1.values[4].x * ((-_96) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        RVar[4u].w = (-_139) + uintBitsToFloat(1065353216u);
        RVar[8u].y = (CBUFFER_1.values[4].y * ((-_114) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
    }
    if (stateVar == 0)
    {
        vec4 _175 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map0, floatBitsToInt(vec4(RVar[5u].yy, 0.0, RVar[5u].y).x)), 1), textureQueryLevels(tex_map0)));
        RVar[7u] = vec4(_175.x, _175.y, RVar[7u].z, RVar[7u].w);
        vec4 _192 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map3, floatBitsToInt(vec4(RVar[5u].yy, 0.0, RVar[5u].y).x)), 1), textureQueryLevels(tex_map3)));
        RVar[5u] = vec4(_192.x, _192.y, RVar[5u].z, RVar[5u].w);
    }
    if (stateVar == 0)
    {
        float _208 = RVar[9u].w;
        float _214 = RVar[0u].w;
        float _218 = RVar[4u].x;
        float _220 = (_214 * CBUFFER_1.values[11].w) + _218;
        float _222 = RVar[0u].w;
        float _226 = RVar[4u].y;
        float _228 = (_222 * CBUFFER_1.values[11].z) + _226;
        float _230 = RVar[7u].x;
        RVar[127u].x = (CBUFFER_1.values[4].z * RVar[4u].w) + uintBitsToFloat(0u);
        RVar[127u].y = (_208 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[123u].z = _220;
        RVar[123u].w = _228;
        RVar[127u].z = float(floatBitsToInt(_230));
        float _241 = RVar[0u].w;
        float _246 = (_241 * CBUFFER_1.values[12].y) + _220;
        float _248 = RVar[0u].w;
        float _252 = (_248 * CBUFFER_1.values[12].x) + _228;
        float _257 = RVar[9u].y;
        float _259 = RVar[8u].y;
        float _267 = RVar[9u].x;
        float _269 = RVar[3u].z;
        float _274 = RVar[7u].y;
        RVar[123u].x = _246;
        RVar[123u].y = _252;
        RVar[3u].z = clamp((CBUFFER_1.values[5].y * _257) + _259, 0.0, 1.0);
        RVar[0u].w = clamp((CBUFFER_1.values[5].x * _267) + _269, 0.0, 1.0);
        RVar[126u].y = float(floatBitsToInt(_274));
        float _291 = RVar[9u].z;
        float _293 = RVar[127u].x;
        float _301 = _252 * uintBitsToFloat(1132396544u);
        float _303 = RVar[127u].z;
        RVar[127u].x = clamp(RVar[127u].y + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[7u].y = clamp((CBUFFER_1.values[5].z * _291) + _293, 0.0, 1.0);
        RVar[126u].z = _246 * uintBitsToFloat(1132396544u);
        RVar[126u].w = _301;
        float _315 = RVar[0u].x;
        float _321 = RVar[0u].z;
        float _326 = RVar[126u].y;
        RVar[126u].x = (-RVar[0u].y) + uintBitsToFloat(1065353216u);
        RVar[127u].w = (-_321) + uintBitsToFloat(1065353216u);
        float _334 = RVar[127u].x;
        float _338 = (_334 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _346 = RVar[126u].z;
        float _349 = RVar[5u].x;
        RVar[9u].x = RVar[3u].x + (_301 * (1.0 / _303));
        RVar[123u].y = _338;
        RVar[4u].z = (CBUFFER_1.values[8].x * ((-_315) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        RVar[127u].x = float(floatBitsToInt(_349));
        float _364 = RVar[3u].y;
        float _369 = RVar[127u].w;
        float _377 = RVar[5u].y;
        RVar[7u].x = (CBUFFER_1.values[8].y * RVar[126u].x) + uintBitsToFloat(0u);
        RVar[9u].y = _364 + (_346 * (1.0 / _326));
        RVar[6u].z = (CBUFFER_1.values[8].z * _369) + uintBitsToFloat(0u);
        RVar[127u].w = clamp(_338 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].z = float(floatBitsToInt(_377));
        float _404 = RVar[127u].x;
        RVar[126u].y = dot(vec4(RVar[2u].x, RVar[2u].y, RVar[2u].z, uintBitsToFloat(2147483648u)), vec4(RVar[2u].x, RVar[2u].y, RVar[2u].z, uintBitsToFloat(0u)));
        float _413 = RVar[126u].w;
        float _417 = RVar[127u].z;
        RVar[127u].x = clamp(RVar[127u].w + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[5u].w = uintBitsToFloat(1065353216u);
        float _425 = RVar[126u].z;
        float _428 = RVar[126u].y;
        float _431 = inversesqrt(_428) * 0.5;
        RVar[3u].x = RVar[6u].x + (_413 * (1.0 / _404));
        float _439 = RVar[6u].y;
        float _442 = RVar[2u].z;
        float _447 = RVar[127u].x;
        float _452 = RVar[2u].y;
        RVar[5u].x = (RVar[2u].x * _431) + uintBitsToFloat(1056964608u);
        RVar[3u].y = _439 + (_425 * (1.0 / _417));
        RVar[5u].z = (_442 * _431) + uintBitsToFloat(1056964608u);
        RVar[8u].w = clamp(_447 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[5u].y = (_452 * _431) + uintBitsToFloat(1056964608u);
    }
    if (stateVar == 0)
    {
        vec4 _475 = texture(tex_map0, vec4(RVar[9u].xy, 0.0, RVar[9u].x).xy);
        RVar[9u] = vec4(_475.x, _475.y, _475.z, RVar[9u].w);
        vec4 _489 = texture(tex_map3, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[2u] = vec4(_489.x, _489.y, _489.z, RVar[2u].w);
    }
    if (stateVar == 0)
    {
        float _500 = RVar[5u].y;
        float _502 = RVar[5u].z;
        float _504 = RVar[5u].w;
        RVar[11u].x = RVar[5u].x;
        RVar[11u].y = _500;
        RVar[11u].z = _502;
        RVar[11u].w = _504;
        float _511 = RVar[9u].z;
        float _516 = RVar[9u].y;
        float _521 = RVar[9u].x;
        float _536 = RVar[2u].y;
        RVar[127u].w = (CBUFFER_1.values[7].x * RVar[2u].x) + uintBitsToFloat(0u);
        RVar[126u].w = (CBUFFER_1.values[7].y * _536) + uintBitsToFloat(0u);
        float _545 = RVar[7u].y;
        float _547 = (CBUFFER_1.values[6].z * ((-_511) + uintBitsToFloat(1065353216u))) + _545;
        float _551 = RVar[3u].z;
        float _553 = (CBUFFER_1.values[6].y * ((-_516) + uintBitsToFloat(1065353216u))) + _551;
        float _557 = RVar[0u].w;
        float _559 = (CBUFFER_1.values[6].x * ((-_521) + uintBitsToFloat(1065353216u))) + _557;
        RVar[123u].y = _547;
        RVar[123u].z = _553;
        RVar[123u].w = _559;
        float _564 = RVar[0u].w;
        float _566 = RVar[9u].x;
        float _569 = clamp((_564 * _566) + _559, 0.0, 1.0);
        float _573 = RVar[2u].z;
        float _576 = (CBUFFER_1.values[7].z * _573) + uintBitsToFloat(0u);
        float _578 = RVar[7u].y;
        float _580 = RVar[9u].z;
        float _583 = clamp((_578 * _580) + _547, 0.0, 1.0);
        float _585 = RVar[3u].z;
        float _587 = RVar[9u].y;
        float _590 = clamp((_585 * _587) + _553, 0.0, 1.0);
        RVar[123u].x = _569;
        RVar[123u].y = _576;
        RVar[123u].z = _583;
        RVar[123u].w = _590;
        float _596 = RVar[126u].w;
        float _600 = RVar[127u].w;
        float _606 = RVar[0u].z;
        float _608 = RVar[6u].z;
        float _611 = clamp((_606 * clamp(_583 + _576, 0.0, 1.0)) + _608, 0.0, 1.0);
        float _613 = RVar[0u].y;
        float _615 = RVar[7u].x;
        float _618 = clamp((_613 * clamp(_590 + _596, 0.0, 1.0)) + _615, 0.0, 1.0);
        float _620 = RVar[0u].x;
        float _622 = RVar[4u].z;
        float _625 = clamp((_620 * clamp(_569 + _600, 0.0, 1.0)) + _622, 0.0, 1.0);
        RVar[126u].y = _611;
        RVar[126u].z = _618;
        RVar[127u].w = _625;
        float _630 = RVar[1u].x;
        float _634 = RVar[1u].z;
        float _638 = RVar[1u].y;
        float _642 = RVar[1u].w;
        float _644 = RVar[127u].w;
        float _646 = ((_630 + (-_625)) * _642) + _644;
        float _648 = RVar[1u].w;
        float _650 = RVar[126u].z;
        float _652 = ((_638 + (-_618)) * _648) + _650;
        float _654 = RVar[1u].w;
        float _656 = RVar[126u].y;
        float _658 = ((_634 + (-_611)) * _654) + _656;
        RVar[8u].x = _646;
        RVar[8u].y = _652;
        RVar[8u].z = _658;
        float _663 = RVar[8u].w;
        RVar[10u].x = _646;
        RVar[10u].y = _652;
        RVar[10u].z = _658;
        RVar[10u].w = _663;
    }
    switch (PS_PUSH.alphaFunc & 255u)
    {
        case 0u:
        {
            discard;
        }
        case 1u:
        {
            if (!(RVar[10u].w < PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 2u:
        {
            if (abs(RVar[10u].w - PS_PUSH.alphaRef) > 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 3u:
        {
            if (!(RVar[10u].w <= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 4u:
        {
            if (!(RVar[10u].w > PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
        case 5u:
        {
            if (abs(RVar[10u].w - PS_PUSH.alphaRef) <= 9.9999997473787516355514526367188e-05)
            {
                discard;
            }
            break;
        }
        case 6u:
        {
            if (!(RVar[10u].w >= PS_PUSH.alphaRef))
            {
                discard;
            }
            break;
        }
    }
    _pixelTmp = RVar[10u];
    uint _739 = PS_PUSH.alphaFunc >> 8u;
    if (_739 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_739 == 2u)
        {
            _pixelTmp = vec4(0.0);
        }
    }
    if ((PS_PUSH.needsPremultiply & 1u) != 0u)
    {
        _pixelTmp *= vec4(_pixelTmp.www, 1.0);
    }
    if (PS_PUSH.uIsSelected != 0) PIXEL_0 = vec4(_pixelTmp.rgb * 0.5f + vec3(1.0f, 0.25f, 0.25f) * 0.5f, _pixelTmp.a); else PIXEL_0 = _pixelTmp; ItemID = PS_PUSH.uItemID;
    _pixelTmp_1 = RVar[11u];
    uint _767 = PS_PUSH.alphaFunc >> 8u;
    if (_767 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_767 == 2u)
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