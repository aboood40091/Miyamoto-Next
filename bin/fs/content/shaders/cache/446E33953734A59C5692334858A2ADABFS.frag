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
uniform sampler2D tex_map3;
uniform sampler2D tex_map0;
uniform sampler2D tex_map2;

layout(location = 0) in vec4 PARAM_0;
layout(location = 1) in vec4 PARAM_1;
layout(location = 2) in vec4 PARAM_2;
layout(location = 3) in vec4 PARAM_3;
layout(location = 4) in vec4 PARAM_4;
layout(location = 5) in vec4 PARAM_5;
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
    RVar[4u] = PARAM_4;
    RVar[5u] = PARAM_5;
    if (stateVar == 0)
    {
        vec4 _68 = texture(tex_map1, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[3u] = vec4(_68.x, RVar[3u].y, RVar[3u].z, _68.w);
        vec4 _83 = texture(tex_map3, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_83.x, RVar[5u].y, RVar[5u].z, _83.w);
    }
    if (stateVar == 0)
    {
        float _100 = RVar[3u].w;
        float _103 = _100 + (-uintBitsToFloat(1056964608u));
        float _105 = RVar[5u].w;
        float _108 = _105 + (-uintBitsToFloat(1056964608u));
        float _110 = RVar[5u].x;
        RVar[5u].x = RVar[3u].x + (-uintBitsToFloat(1056964608u));
        RVar[5u].y = uintBitsToFloat(0u);
        RVar[7u].x = _110 + (-uintBitsToFloat(1056964608u));
        RVar[3u].x = _108 * CBUFFER_1.values[13].y;
        RVar[3u].y = _103 * CBUFFER_1.values[11].x;
        RVar[2u].z = _108 * CBUFFER_1.values[13].x;
        RVar[3u].w = _103 * CBUFFER_1.values[11].y;
        RVar[9u].w = uintBitsToFloat(1065353216u);
    }
    if (stateVar == 0)
    {
        vec4 _166 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map0, floatBitsToInt(vec4(RVar[5u].yy, 0.0, RVar[5u].y).x)), 1), textureQueryLevels(tex_map0)));
        RVar[6u] = vec4(_166.x, _166.y, RVar[6u].z, RVar[6u].w);
        vec4 _183 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map2, floatBitsToInt(vec4(RVar[5u].yy, 0.0, RVar[5u].y).x)), 1), textureQueryLevels(tex_map2)));
        RVar[8u] = vec4(_183.x, _183.y, RVar[8u].z, RVar[8u].w);
    }
    if (stateVar == 0)
    {
        float _193 = RVar[5u].x;
        float _197 = RVar[3u].y;
        float _199 = (_193 * CBUFFER_1.values[11].z) + _197;
        float _201 = RVar[7u].x;
        float _205 = RVar[2u].z;
        float _207 = (_201 * CBUFFER_1.values[13].z) + _205;
        float _209 = RVar[5u].x;
        float _213 = RVar[3u].w;
        float _215 = (_209 * CBUFFER_1.values[11].w) + _213;
        float _217 = RVar[7u].x;
        float _221 = RVar[3u].x;
        float _223 = (_217 * CBUFFER_1.values[13].w) + _221;
        float _225 = RVar[6u].y;
        RVar[123u].x = _199;
        RVar[123u].y = _207;
        RVar[123u].z = _215;
        RVar[123u].w = _223;
        RVar[127u].y = float(floatBitsToInt(_225));
        float _236 = RVar[7u].x;
        float _241 = (_236 * CBUFFER_1.values[14].y) + _223;
        float _243 = RVar[5u].x;
        float _248 = (_243 * CBUFFER_1.values[12].x) + _199;
        float _250 = RVar[7u].x;
        float _254 = (_250 * CBUFFER_1.values[14].x) + _207;
        float _256 = RVar[5u].x;
        float _260 = (_256 * CBUFFER_1.values[12].y) + _215;
        float _262 = RVar[6u].x;
        RVar[123u].x = _241;
        RVar[123u].y = _248;
        RVar[123u].z = _254;
        RVar[123u].w = _260;
        RVar[126u].x = _254 * uintBitsToFloat(1132396544u);
        RVar[126u].y = _260 * uintBitsToFloat(1132396544u);
        RVar[126u].w = _241 * uintBitsToFloat(1132396544u);
        float _289 = (CBUFFER_1.values[4].x * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _295 = (CBUFFER_1.values[4].y * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _304 = RVar[127u].y;
        RVar[123u].x = _289;
        RVar[123u].y = _295;
        RVar[127u].w = (CBUFFER_1.values[4].z * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _320 = RVar[126u].y;
        float _323 = RVar[8u].x;
        RVar[5u].x = RVar[2u].x + ((_248 * uintBitsToFloat(1132396544u)) * (1.0 / float(floatBitsToInt(_262))));
        RVar[127u].x = float(floatBitsToInt(_323));
        float _329 = RVar[127u].w;
        float _343 = RVar[8u].y;
        RVar[5u].y = RVar[2u].y + (_320 * (1.0 / _304));
        RVar[126u].y = float(floatBitsToInt(_343));
        float _350 = clamp(clamp(clamp(_289 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _355 = RVar[1u].z;
        float _357 = RVar[1u].z;
        float _363 = RVar[127u].x;
        RVar[127u].x = _350;
        RVar[8u].y = clamp(clamp(clamp(_295 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _368 = RVar[1u].y;
        float _370 = RVar[1u].y;
        float _372 = (_368 * _370) + (_355 * _357);
        float _374 = RVar[0u].x;
        float _379 = clamp(clamp(clamp(_329 + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _381 = RVar[126u].x;
        float _384 = RVar[126u].y;
        RVar[123u].x = _372;
        RVar[126u].y = _374 + (-_350);
        RVar[127u].z = _379;
        float _393 = RVar[1u].x;
        float _395 = RVar[1u].x;
        float _397 = (_393 * _395) + _372;
        float _399 = RVar[126u].w;
        float _402 = RVar[0u].y;
        float _404 = RVar[8u].y;
        float _408 = RVar[0u].z;
        RVar[2u].x = RVar[4u].x + (_381 * (1.0 / _363));
        RVar[123u].y = _397;
        RVar[3u].w = _402 + (-_404);
        float _423 = RVar[4u].y;
        float _426 = RVar[0u].w;
        float _428 = RVar[127u].z;
        RVar[6u].x = (RVar[126u].y * RVar[0u].w) + RVar[127u].x;
        RVar[2u].y = _423 + (_399 * (1.0 / _384));
        RVar[6u].z = ((_408 + (-_379)) * _426) + _428;
        RVar[4u].x = inversesqrt(_397) * 0.5;
    }
    if (stateVar == 0)
    {
        RVar[5u] = vec4(texture(tex_map0, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy).w, RVar[5u].y, RVar[5u].z, RVar[5u].w);
        RVar[2u] = vec4(texture(tex_map2, vec4(RVar[2u].xy, 0.0, RVar[2u].x).xy).w, RVar[2u].y, RVar[2u].z, RVar[2u].w);
    }
    if (stateVar == 0)
    {
        float _483 = RVar[2u].x;
        float _489 = RVar[5u].x;
        float _493 = (_489 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _495 = RVar[1u].y;
        float _497 = RVar[4u].x;
        RVar[6u].y = (RVar[3u].w * RVar[0u].w) + RVar[8u].y;
        RVar[127u].z = (_483 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[123u].w = _493;
        RVar[9u].y = (_495 * _497) + uintBitsToFloat(1056964608u);
        float _516 = RVar[1u].z;
        float _518 = RVar[4u].x;
        RVar[9u].x = (RVar[1u].x * RVar[4u].x) + uintBitsToFloat(1056964608u);
        RVar[9u].z = (_516 * _518) + uintBitsToFloat(1056964608u);
        float _525 = RVar[127u].z;
        float _532 = (CBUFFER_1.values[4].w * clamp(clamp(_493 + uintBitsToFloat(0u), 0.0, 1.0) + _525, 0.0, 1.0)) + uintBitsToFloat(0u);
        RVar[123u].y = _532;
        RVar[6u].w = clamp(_532 + uintBitsToFloat(0u), 0.0, 1.0);
        float _541 = RVar[9u].y;
        float _543 = RVar[9u].z;
        float _545 = RVar[9u].w;
        RVar[1u].x = RVar[9u].x;
        RVar[1u].y = _541;
        RVar[1u].z = _543;
        RVar[1u].w = _545;
        float _553 = RVar[6u].y;
        float _555 = RVar[6u].z;
        float _557 = RVar[6u].w;
        RVar[0u].x = RVar[6u].x;
        RVar[0u].y = _553;
        RVar[0u].z = _555;
        RVar[0u].w = _557;
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
    uint _632 = PS_PUSH.alphaFunc >> 8u;
    if (_632 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_632 == 2u)
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
    uint _660 = PS_PUSH.alphaFunc >> 8u;
    if (_660 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_660 == 2u)
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