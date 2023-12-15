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

uniform sampler2D tex_map3;
uniform sampler2D tex_map5;
uniform sampler2D tex_map2;
uniform sampler2D tex_map0;
uniform sampler2D tex_map1;
uniform sampler2D tex_map4;

layout(location = 2) in vec4 PARAM_2;
layout(location = 1) in vec4 PARAM_1;
layout(location = 0) in vec4 PARAM_0;
layout(location = 3) in vec4 PARAM_3;
layout(location = 4) in vec4 PARAM_4;
layout(location = 5) in vec4 PARAM_5;
layout(location = 6) in vec4 PARAM_6;
layout(location = 7) in vec4 PARAM_7;
layout(location = 8) in vec4 PARAM_8;
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
    RVar[5u] = PARAM_5;
    RVar[6u] = PARAM_6;
    RVar[7u] = PARAM_7;
    RVar[8u] = PARAM_8;
    if (stateVar == 0)
    {
        vec4 _80 = texture(tex_map3, vec4(RVar[6u].xy, 0.0, RVar[6u].x).xy);
        RVar[6u] = vec4(_80.x, RVar[6u].y, RVar[6u].z, _80.w);
        vec4 _95 = texture(tex_map5, vec4(RVar[8u].xy, 0.0, RVar[8u].x).xy);
        RVar[8u] = vec4(_95.x, RVar[8u].y, RVar[8u].z, _95.w);
        RVar[5u] = texture(tex_map2, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
    }
    if (stateVar == 0)
    {
        float _118 = RVar[6u].w;
        float _122 = _118 + (-uintBitsToFloat(1056964608u));
        float _130 = RVar[0u].w;
        float _132 = RVar[5u].w;
        float _137 = RVar[8u].x;
        RVar[127u].y = RVar[6u].x + (-uintBitsToFloat(1056964608u));
        RVar[0u].z = uintBitsToFloat(0u);
        RVar[126u].w = (_130 * _132) + uintBitsToFloat(0u);
        RVar[127u].z = _137 + (-uintBitsToFloat(1056964608u));
        float _157 = RVar[8u].w;
        float _160 = _157 + (-uintBitsToFloat(1056964608u));
        float _170 = (-CBUFFER_1.values[7].w) + uintBitsToFloat(1065353216u);
        RVar[127u].w = _170;
        float _177 = RVar[127u].y;
        float _181 = (_177 * CBUFFER_1.values[11].z) + (_122 * CBUFFER_1.values[11].x);
        float _186 = RVar[127u].y;
        float _190 = (_186 * CBUFFER_1.values[11].w) + (_122 * CBUFFER_1.values[11].y);
        float _192 = RVar[5u].x;
        RVar[123u].y = _181;
        RVar[123u].w = _190;
        RVar[10u].y = (_192 * _170) + uintBitsToFloat(0u);
        float _202 = RVar[127u].y;
        float _207 = (_202 * CBUFFER_1.values[12].x) + _181;
        float _209 = RVar[127u].z;
        float _213 = (_209 * CBUFFER_1.values[13].z) + (_160 * CBUFFER_1.values[13].x);
        float _215 = RVar[127u].y;
        float _219 = (_215 * CBUFFER_1.values[12].y) + _190;
        float _221 = RVar[127u].z;
        float _225 = (_221 * CBUFFER_1.values[13].w) + (_160 * CBUFFER_1.values[13].y);
        float _227 = RVar[5u].y;
        float _229 = RVar[127u].w;
        RVar[123u].x = _207;
        RVar[123u].y = _213;
        RVar[123u].z = _219;
        RVar[123u].w = _225;
        RVar[11u].x = (_227 * _229) + uintBitsToFloat(0u);
        float _240 = RVar[127u].z;
        float _245 = (_240 * CBUFFER_1.values[14].x) + _213;
        float _250 = RVar[127u].z;
        float _254 = (_250 * CBUFFER_1.values[14].y) + _225;
        float _258 = RVar[5u].z;
        float _260 = RVar[127u].w;
        RVar[123u].x = _245;
        RVar[6u].y = _207 * uintBitsToFloat(1132396544u);
        RVar[123u].z = _254;
        RVar[5u].w = _219 * uintBitsToFloat(1132396544u);
        RVar[8u].w = (_258 * _260) + uintBitsToFloat(0u);
        RVar[10u].x = clamp(RVar[126u].w + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[9u].y = _254 * uintBitsToFloat(1132396544u);
        RVar[5u].z = _245 * uintBitsToFloat(1132396544u);
    }
    if (stateVar == 0)
    {
        vec4 _304 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map0, floatBitsToInt(vec4(RVar[0u].zz, 0.0, RVar[0u].z).x)), 1), textureQueryLevels(tex_map0)));
        RVar[5u] = vec4(_304.x, _304.y, RVar[5u].z, RVar[5u].w);
        vec4 _320 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map1, floatBitsToInt(vec4(RVar[0u].zz, 0.0, RVar[0u].z).x)), 1), textureQueryLevels(tex_map1)));
        RVar[8u] = vec4(_320.x, _320.y, RVar[8u].z, RVar[8u].w);
        vec4 _336 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map4, floatBitsToInt(vec4(RVar[0u].zz, 0.0, RVar[0u].z).x)), 1), textureQueryLevels(tex_map4)));
        RVar[0u] = vec4(_336.x, _336.y, RVar[0u].z, RVar[0u].w);
    }
    if (stateVar == 0)
    {
        RVar[127u].x = float(floatBitsToInt(RVar[5u].x));
        RVar[126u].w = float(floatBitsToInt(RVar[5u].y));
        float _361 = RVar[126u].w;
        float _367 = RVar[5u].w;
        float _370 = RVar[8u].x;
        RVar[5u].x = RVar[3u].x + (RVar[6u].y * (1.0 / RVar[127u].x));
        RVar[127u].x = float(floatBitsToInt(_370));
        float _379 = RVar[8u].y;
        RVar[5u].y = RVar[3u].y + (_367 * (1.0 / _361));
        RVar[127u].z = float(floatBitsToInt(_379));
        float _391 = RVar[127u].z;
        float _397 = RVar[5u].w;
        float _400 = RVar[0u].x;
        RVar[6u].x = RVar[4u].x + (RVar[6u].y * (1.0 / RVar[127u].x));
        RVar[126u].w = float(floatBitsToInt(_400));
        float _409 = RVar[0u].y;
        RVar[6u].y = RVar[4u].y + (_397 * (1.0 / _391));
        RVar[127u].z = float(floatBitsToInt(_409));
        float _421 = RVar[127u].z;
        float _427 = RVar[9u].y;
        RVar[9u].x = RVar[7u].x + (RVar[5u].z * (1.0 / RVar[126u].w));
        RVar[9u].y = RVar[7u].y + (_427 * (1.0 / _421));
    }
    if (stateVar == 0)
    {
        vec4 _448 = texture(tex_map0, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_448.x, _448.y, _448.z, RVar[5u].w);
        vec4 _462 = texture(tex_map1, vec4(RVar[6u].xy, 0.0, RVar[6u].x).xy);
        RVar[6u] = vec4(_462.x, _462.y, _462.z, RVar[6u].w);
        RVar[9u] = texture(tex_map4, vec4(RVar[9u].xy, 0.0, RVar[9u].x).xy);
    }
    if (stateVar == 0)
    {
        float _483 = RVar[5u].x;
        float _495 = RVar[5u].z;
        float _500 = RVar[5u].y;
        float _505 = RVar[6u].x;
        RVar[127u].y = (RVar[10u].x * RVar[9u].w) + uintBitsToFloat(0u);
        RVar[127u].x = (_505 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _517 = (CBUFFER_1.values[5].y * ((-_500) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _522 = (CBUFFER_1.values[5].x * ((-_483) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _524 = RVar[6u].y;
        float _528 = (_524 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _533 = (CBUFFER_1.values[5].z * ((-_495) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _535 = RVar[6u].z;
        RVar[123u].x = _517;
        RVar[123u].y = _522;
        RVar[123u].z = _528;
        RVar[123u].w = _533;
        RVar[127u].z = (_535 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _546 = RVar[127u].x;
        float _561 = RVar[5u].x;
        float _568 = RVar[5u].z;
        RVar[126u].y = clamp((CBUFFER_1.values[4].y * RVar[5u].y) + _517, 0.0, 1.0);
        RVar[126u].z = clamp((CBUFFER_1.values[4].x * _561) + _522, 0.0, 1.0);
        RVar[126u].w = clamp((CBUFFER_1.values[4].z * _568) + _533, 0.0, 1.0);
        float _587 = RVar[11u].x;
        float _590 = clamp((clamp(_528 + uintBitsToFloat(0u), 0.0, 1.0) * CBUFFER_1.values[7].w) + _587, 0.0, 1.0);
        float _594 = RVar[10u].y;
        float _597 = clamp((clamp(_546 + uintBitsToFloat(0u), 0.0, 1.0) * CBUFFER_1.values[7].w) + _594, 0.0, 1.0);
        float _599 = RVar[127u].z;
        float _604 = RVar[9u].y;
        RVar[127u].x = (RVar[9u].x * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[123u].y = _590;
        RVar[123u].z = _597;
        RVar[127u].z = (_604 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _616 = RVar[8u].w;
        float _619 = clamp((clamp(_599 + uintBitsToFloat(0u), 0.0, 1.0) * CBUFFER_1.values[7].w) + _616, 0.0, 1.0);
        float _624 = (CBUFFER_1.values[7].x * _597) + uintBitsToFloat(0u);
        float _629 = (CBUFFER_1.values[7].y * _590) + uintBitsToFloat(0u);
        float _631 = RVar[9u].z;
        float _637 = RVar[127u].y;
        RVar[123u].x = _619;
        RVar[123u].y = _624;
        RVar[123u].z = _629;
        RVar[127u].w = (_631 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[9u].w = clamp((_637 + uintBitsToFloat(0u)) * 0.5, 0.0, 1.0);
        float _649 = RVar[2u].z;
        float _651 = RVar[2u].z;
        float _654 = RVar[126u].y;
        float _658 = RVar[126u].z;
        float _665 = (CBUFFER_1.values[7].z * _619) + uintBitsToFloat(0u);
        RVar[123u].w = _665;
        RVar[8u].w = uintBitsToFloat(1065353216u);
        float _670 = RVar[126u].w;
        float _674 = RVar[127u].x;
        float _676 = clamp(clamp(_658 + _624, 0.0, 1.0) + _674, 0.0, 1.0);
        float _678 = RVar[127u].z;
        float _680 = clamp(clamp(_654 + _629, 0.0, 1.0) + _678, 0.0, 1.0);
        float _682 = RVar[2u].y;
        float _684 = RVar[2u].y;
        float _686 = (_682 * _684) + (_649 * _651);
        RVar[126u].y = _676;
        RVar[126u].w = _680;
        RVar[122u].x = _686;
        float _692 = RVar[1u].x;
        float _696 = RVar[2u].x;
        float _698 = RVar[2u].x;
        float _700 = (_696 * _698) + _686;
        float _702 = RVar[127u].w;
        float _704 = clamp(clamp(_670 + _665, 0.0, 1.0) + _702, 0.0, 1.0);
        float _706 = RVar[1u].y;
        RVar[123u].y = _700;
        RVar[127u].z = _704;
        float _718 = RVar[1u].w;
        float _720 = RVar[126u].w;
        float _724 = RVar[1u].z;
        float _728 = inversesqrt(_700) * 0.5;
        RVar[9u].x = ((_692 + (-_676)) * RVar[1u].w) + RVar[126u].y;
        RVar[9u].y = ((_706 + (-_680)) * _718) + _720;
        float _732 = RVar[2u].x;
        float _735 = (_732 * _728) + uintBitsToFloat(1056964608u);
        float _737 = RVar[2u].y;
        float _740 = (_737 * _728) + uintBitsToFloat(1056964608u);
        float _742 = RVar[1u].w;
        float _744 = RVar[127u].z;
        float _748 = RVar[2u].z;
        float _751 = (_748 * _728) + uintBitsToFloat(1056964608u);
        RVar[8u].x = _735;
        RVar[8u].y = _740;
        RVar[9u].z = ((_724 + (-_704)) * _742) + _744;
        RVar[8u].z = _751;
        float _757 = RVar[8u].w;
        RVar[1u].x = _735;
        RVar[1u].y = _740;
        RVar[1u].z = _751;
        RVar[1u].w = _757;
        float _765 = RVar[9u].y;
        float _767 = RVar[9u].z;
        float _769 = RVar[9u].w;
        RVar[0u].x = RVar[9u].x;
        RVar[0u].y = _765;
        RVar[0u].z = _767;
        RVar[0u].w = _769;
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
    uint _844 = PS_PUSH.alphaFunc >> 8u;
    if (_844 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_844 == 2u)
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
    uint _872 = PS_PUSH.alphaFunc >> 8u;
    if (_872 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_872 == 2u)
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