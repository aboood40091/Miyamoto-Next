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

uniform sampler2D tex_map2;
uniform sampler2D tex_map0;
uniform sampler2D tex_map1;
uniform sampler2D tex_map3;

layout(location = 1) in vec4 PARAM_1;
layout(location = 0) in vec4 PARAM_0;
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
    RVar[0u] = PARAM_1;
    RVar[1u] = PARAM_0;
    RVar[2u] = PARAM_3;
    RVar[3u] = PARAM_4;
    RVar[4u] = PARAM_5;
    RVar[5u] = PARAM_6;
    if (stateVar == 0)
    {
        vec4 _68 = texture(tex_map2, vec4(RVar[4u].xy, 0.0, RVar[4u].x).xy);
        RVar[4u] = vec4(_68.x, RVar[4u].y, RVar[4u].z, _68.w);
        RVar[2u] = texture(tex_map0, vec4(RVar[2u].xy, 0.0, RVar[2u].x).xy);
        vec4 _96 = texture(tex_map1, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[7u] = vec4(_96.x, _96.y, _96.z, RVar[7u].w);
        vec4 _112 = texture(tex_map3, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[6u] = vec4(_112.x, _112.y, _112.z, RVar[6u].w);
    }
    if (stateVar == 0)
    {
        float _123 = RVar[4u].w;
        float _127 = _123 + (-uintBitsToFloat(1056964608u));
        float _143 = RVar[2u].x;
        float _146 = (CBUFFER_1.values[6].x * _143) + uintBitsToFloat(0u);
        float _150 = RVar[2u].y;
        RVar[5u].y = RVar[4u].x + (-uintBitsToFloat(1056964608u));
        RVar[3u].z = uintBitsToFloat(0u);
        RVar[123u].w = _146;
        RVar[4u].z = (CBUFFER_1.values[6].y * _150) + uintBitsToFloat(0u);
        float _169 = RVar[2u].z;
        RVar[2u].x = (RVar[2u].w * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[2u].y = (CBUFFER_1.values[6].z * _169) + uintBitsToFloat(0u);
        RVar[2u].z = _127 * CBUFFER_1.values[11].y;
        RVar[2u].w = _127 * CBUFFER_1.values[11].x;
        RVar[5u].x = clamp(_146 + uintBitsToFloat(0u), 0.0, 1.0);
    }
    if (stateVar == 0)
    {
        vec4 _208 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map1, floatBitsToInt(vec4(RVar[3u].zz, 0.0, RVar[3u].z).x)), 1), textureQueryLevels(tex_map1)));
        RVar[4u] = vec4(_208.x, _208.y, RVar[4u].z, RVar[4u].w);
    }
    if (stateVar == 0)
    {
        float _217 = RVar[5u].y;
        float _221 = RVar[2u].z;
        float _223 = (_217 * CBUFFER_1.values[11].w) + _221;
        float _225 = RVar[5u].y;
        float _229 = RVar[2u].w;
        float _231 = (_225 * CBUFFER_1.values[11].z) + _229;
        float _233 = RVar[2u].y;
        float _238 = RVar[4u].z;
        float _243 = RVar[4u].x;
        RVar[123u].x = _223;
        RVar[123u].y = _231;
        RVar[4u].z = clamp(_233 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[2u].w = clamp(_238 + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[127u].w = float(floatBitsToInt(_243));
        float _264 = RVar[5u].y;
        float _269 = (_264 * CBUFFER_1.values[12].y) + _223;
        float _271 = RVar[5u].y;
        float _275 = (_271 * CBUFFER_1.values[12].x) + _231;
        float _277 = RVar[4u].y;
        RVar[2u].x = clamp(RVar[2u].x + uintBitsToFloat(0u), 0.0, 1.0);
        RVar[4u].y = (-CBUFFER_1.values[7].x) + uintBitsToFloat(1065353216u);
        RVar[123u].z = _269;
        RVar[123u].w = _275;
        RVar[127u].z = float(floatBitsToInt(_277));
        float _301 = RVar[127u].w;
        RVar[127u].x = _269 * uintBitsToFloat(1132396544u);
        RVar[2u].z = (-CBUFFER_1.values[7].y) + uintBitsToFloat(1065353216u);
        RVar[4u].w = (-CBUFFER_1.values[7].z) + uintBitsToFloat(1065353216u);
        float _317 = RVar[6u].y;
        float _324 = RVar[6u].x;
        float _330 = RVar[127u].z;
        RVar[4u].x = (CBUFFER_1.values[4].w * RVar[6u].z) + uintBitsToFloat(0u);
        RVar[5u].y = (CBUFFER_1.values[4].w * _317) + uintBitsToFloat(0u);
        RVar[3u].z = (CBUFFER_1.values[4].w * _324) + uintBitsToFloat(0u);
        float _339 = RVar[127u].x;
        float _343 = RVar[1u].z;
        float _345 = RVar[1u].z;
        RVar[6u].x = RVar[3u].x + ((_275 * uintBitsToFloat(1132396544u)) * (1.0 / _301));
        RVar[8u].w = uintBitsToFloat(1065353216u);
        float _357 = RVar[3u].y;
        RVar[3u].x = (RVar[1u].y * RVar[1u].y) + (_343 * _345);
        RVar[6u].y = _357 + (_339 * (1.0 / _330));
    }
    if (stateVar == 0)
    {
        RVar[6u] = texture(tex_map1, vec4(RVar[6u].xy, 0.0, RVar[6u].x).xy);
    }
    if (stateVar == 0)
    {
        float _381 = RVar[2u].x;
        float _383 = RVar[6u].w;
        float _386 = (_381 * _383) + uintBitsToFloat(0u);
        float _388 = RVar[6u].z;
        float _393 = RVar[6u].y;
        float _398 = RVar[6u].x;
        RVar[123u].x = _386;
        float _408 = (CBUFFER_1.values[5].x * ((-_398) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _410 = RVar[6u].w;
        float _416 = (CBUFFER_1.values[5].z * ((-_388) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _421 = (CBUFFER_1.values[5].y * ((-_393) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _423 = RVar[1u].x;
        float _425 = RVar[1u].x;
        float _427 = RVar[3u].x;
        float _429 = (_423 * _425) + _427;
        RVar[123u].x = _408;
        RVar[123u].z = _416;
        RVar[123u].w = _421;
        RVar[122u].x = _429;
        float _438 = RVar[6u].y;
        float _441 = clamp((CBUFFER_1.values[4].y * _438) + _421, 0.0, 1.0);
        float _445 = RVar[6u].x;
        float _448 = clamp((CBUFFER_1.values[4].x * _445) + _408, 0.0, 1.0);
        float _458 = RVar[6u].z;
        float _461 = clamp((CBUFFER_1.values[4].z * _458) + _416, 0.0, 1.0);
        float _464 = inversesqrt(_429) * 0.5;
        RVar[123u].x = _441;
        RVar[123u].y = _448;
        RVar[123u].w = _461;
        RVar[127u].x = _464;
        float _470 = RVar[5u].x;
        float _472 = RVar[4u].y;
        float _474 = (_470 * _472) + _448;
        float _479 = RVar[4u].z;
        float _481 = RVar[4u].w;
        float _483 = (_479 * _481) + _461;
        float _485 = RVar[2u].w;
        float _487 = RVar[2u].z;
        float _489 = (_485 * _487) + _441;
        float _491 = RVar[1u].x;
        RVar[123u].x = _474;
        RVar[123u].z = _483;
        RVar[123u].w = _489;
        RVar[8u].x = (_491 * _464) + uintBitsToFloat(1056964608u);
        float _500 = RVar[7u].y;
        float _505 = clamp((_500 * CBUFFER_1.values[7].y) + _489, 0.0, 1.0);
        float _507 = RVar[7u].x;
        float _512 = clamp((_507 * CBUFFER_1.values[7].x) + _474, 0.0, 1.0);
        float _514 = RVar[1u].z;
        float _516 = RVar[127u].x;
        float _521 = RVar[7u].z;
        float _526 = clamp((_521 * CBUFFER_1.values[7].z) + _483, 0.0, 1.0);
        RVar[123u].x = _505;
        RVar[123u].y = _512;
        RVar[8u].z = (_514 * _516) + uintBitsToFloat(1056964608u);
        RVar[123u].w = _526;
        RVar[7u].w = clamp(clamp(clamp(((_410 + _386) + (-uintBitsToFloat(1056964608u))) * 2.0, 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _536 = RVar[4u].x;
        float _538 = clamp(_526 + _536, 0.0, 1.0);
        float _540 = RVar[5u].y;
        float _542 = clamp(_505 + _540, 0.0, 1.0);
        float _544 = RVar[3u].z;
        float _546 = clamp(_512 + _544, 0.0, 1.0);
        float _548 = RVar[1u].y;
        float _550 = RVar[127u].x;
        RVar[127u].y = _538;
        RVar[127u].z = _542;
        RVar[127u].w = _546;
        RVar[8u].y = (_548 * _550) + uintBitsToFloat(1056964608u);
        float _563 = RVar[0u].z;
        float _567 = RVar[0u].y;
        float _577 = RVar[0u].w;
        float _579 = RVar[127u].z;
        float _583 = RVar[0u].w;
        float _585 = RVar[127u].y;
        RVar[7u].x = ((RVar[0u].x + (-_546)) * RVar[0u].w) + RVar[127u].w;
        RVar[7u].y = ((_567 + (-_542)) * _577) + _579;
        RVar[7u].z = ((_563 + (-_538)) * _583) + _585;
        float _594 = RVar[8u].y;
        float _596 = RVar[8u].z;
        float _598 = RVar[8u].w;
        RVar[1u].x = RVar[8u].x;
        RVar[1u].y = _594;
        RVar[1u].z = _596;
        RVar[1u].w = _598;
        float _606 = RVar[7u].y;
        float _608 = RVar[7u].z;
        float _610 = RVar[7u].w;
        RVar[0u].x = RVar[7u].x;
        RVar[0u].y = _606;
        RVar[0u].z = _608;
        RVar[0u].w = _610;
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
    uint _685 = PS_PUSH.alphaFunc >> 8u;
    if (_685 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_685 == 2u)
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
    uint _713 = PS_PUSH.alphaFunc >> 8u;
    if (_713 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_713 == 2u)
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