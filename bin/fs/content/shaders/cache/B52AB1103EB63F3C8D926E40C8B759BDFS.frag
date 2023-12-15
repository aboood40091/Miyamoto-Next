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
    RVar[0u] = PARAM_0;
    RVar[1u] = PARAM_1;
    RVar[2u] = PARAM_3;
    RVar[3u] = PARAM_4;
    RVar[4u] = PARAM_5;
    RVar[5u] = PARAM_6;
    if (stateVar == 0)
    {
        vec4 _68 = texture(tex_map1, vec4(RVar[3u].xy, 0.0, RVar[3u].x).xy);
        RVar[3u] = vec4(_68.x, RVar[3u].y, RVar[3u].z, _68.w);
        vec4 _83 = texture(tex_map3, vec4(RVar[5u].xy, 0.0, RVar[5u].x).xy);
        RVar[5u] = vec4(_83.x, RVar[5u].y, RVar[5u].z, _83.w);
    }
    if (stateVar == 0)
    {
        float _94 = RVar[3u].w;
        float _98 = _94 + (-uintBitsToFloat(1056964608u));
        float _100 = RVar[3u].x;
        float _105 = RVar[5u].w;
        float _108 = _105 + (-uintBitsToFloat(1056964608u));
        float _110 = RVar[5u].x;
        RVar[3u].x = uintBitsToFloat(0u);
        RVar[3u].z = _100 + (-uintBitsToFloat(1056964608u));
        RVar[5u].w = _110 + (-uintBitsToFloat(1056964608u));
        RVar[5u].x = _98 * CBUFFER_1.values[11].y;
        RVar[5u].y = _108 * CBUFFER_1.values[13].x;
        RVar[2u].z = _108 * CBUFFER_1.values[13].y;
        RVar[3u].w = _98 * CBUFFER_1.values[11].x;
        RVar[7u].w = uintBitsToFloat(1065353216u);
    }
    if (stateVar == 0)
    {
        vec4 _165 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map0, floatBitsToInt(vec4(RVar[3u].xx, 0.0, RVar[3u].x).x)), 1), textureQueryLevels(tex_map0)));
        RVar[6u] = vec4(_165.x, _165.y, RVar[6u].z, RVar[6u].w);
        vec4 _182 = intBitsToFloat(ivec4(ivec3(textureSize(tex_map2, floatBitsToInt(vec4(RVar[3u].xx, 0.0, RVar[3u].x).x)), 1), textureQueryLevels(tex_map2)));
        RVar[3u] = vec4(_182.x, _182.y, RVar[3u].z, RVar[3u].w);
    }
    if (stateVar == 0)
    {
        float _191 = RVar[5u].w;
        float _195 = RVar[2u].z;
        float _197 = (_191 * CBUFFER_1.values[13].w) + _195;
        float _199 = RVar[3u].z;
        float _203 = RVar[5u].x;
        float _205 = (_199 * CBUFFER_1.values[11].w) + _203;
        float _207 = RVar[3u].z;
        float _211 = RVar[3u].w;
        float _213 = (_207 * CBUFFER_1.values[11].z) + _211;
        float _215 = RVar[5u].w;
        float _219 = RVar[5u].y;
        float _221 = (_215 * CBUFFER_1.values[13].z) + _219;
        float _223 = RVar[6u].x;
        RVar[123u].x = _197;
        RVar[123u].y = _205;
        RVar[123u].z = _213;
        RVar[123u].w = _221;
        RVar[127u].y = float(floatBitsToInt(_223));
        float _234 = RVar[3u].z;
        float _239 = (_234 * CBUFFER_1.values[12].y) + _205;
        float _241 = RVar[5u].w;
        float _246 = (_241 * CBUFFER_1.values[14].x) + _221;
        float _248 = RVar[5u].w;
        float _252 = (_248 * CBUFFER_1.values[14].y) + _197;
        float _254 = RVar[3u].z;
        float _258 = (_254 * CBUFFER_1.values[12].x) + _213;
        float _260 = RVar[6u].y;
        RVar[123u].x = _239;
        RVar[123u].y = _246;
        RVar[123u].z = _252;
        RVar[123u].w = _258;
        RVar[127u].x = float(floatBitsToInt(_260));
        float _278 = RVar[127u].y;
        RVar[126u].x = _252 * uintBitsToFloat(1132396544u);
        RVar[127u].y = _239 * uintBitsToFloat(1132396544u);
        RVar[127u].w = _246 * uintBitsToFloat(1132396544u);
        float _285 = RVar[1u].z;
        float _287 = RVar[1u].z;
        float _291 = RVar[127u].x;
        float _297 = RVar[1u].y;
        float _299 = RVar[1u].y;
        float _301 = (_297 * _299) + (_285 * _287);
        float _303 = RVar[127u].y;
        float _306 = RVar[3u].x;
        RVar[6u].x = RVar[2u].x + ((_258 * uintBitsToFloat(1132396544u)) * (1.0 / _278));
        RVar[123u].y = _301;
        RVar[127u].y = float(floatBitsToInt(_306));
        float _319 = RVar[2u].y;
        float _322 = RVar[3u].y;
        RVar[125u].x = (RVar[1u].x * RVar[1u].x) + _301;
        RVar[6u].y = _319 + (_303 * (1.0 / _291));
        RVar[127u].x = float(floatBitsToInt(_322));
        float _336 = RVar[127u].x;
        float _342 = RVar[126u].x;
        float _345 = RVar[125u].x;
        float _349 = inversesqrt(_345) * 0.5;
        RVar[2u].x = RVar[4u].x + (RVar[127u].w * (1.0 / RVar[127u].y));
        float _357 = RVar[4u].y;
        float _360 = RVar[1u].z;
        float _365 = RVar[1u].y;
        RVar[7u].x = (RVar[1u].x * _349) + uintBitsToFloat(1056964608u);
        RVar[2u].y = _357 + (_342 * (1.0 / _336));
        RVar[7u].z = (_360 * _349) + uintBitsToFloat(1056964608u);
        RVar[7u].y = (_365 * _349) + uintBitsToFloat(1056964608u);
    }
    if (stateVar == 0)
    {
        RVar[6u] = texture(tex_map0, vec4(RVar[6u].xy, 0.0, RVar[6u].x).xy);
        RVar[2u] = texture(tex_map2, vec4(RVar[2u].xy, 0.0, RVar[2u].x).xy);
    }
    if (stateVar == 0)
    {
        float _406 = RVar[6u].y;
        float _410 = (_406 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _412 = RVar[6u].x;
        float _416 = (_412 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _418 = RVar[2u].x;
        float _424 = RVar[6u].z;
        float _428 = (_424 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _430 = RVar[2u].y;
        RVar[123u].x = _410;
        RVar[123u].y = _416;
        RVar[127u].z = (_418 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[123u].w = _428;
        RVar[126u].x = (_430 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _450 = RVar[2u].z;
        float _454 = (_450 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        float _456 = RVar[6u].w;
        float _460 = (_456 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[123u].w = _454;
        RVar[122u].x = _460;
        float _465 = clamp(clamp(_428 + uintBitsToFloat(0u), 0.0, 1.0) + _454, 0.0, 1.0);
        float _467 = RVar[126u].x;
        float _469 = clamp(clamp(_410 + uintBitsToFloat(0u), 0.0, 1.0) + _467, 0.0, 1.0);
        float _471 = RVar[127u].z;
        float _473 = clamp(clamp(_416 + uintBitsToFloat(0u), 0.0, 1.0) + _471, 0.0, 1.0);
        float _478 = RVar[2u].w;
        float _482 = (_478 * uintBitsToFloat(1065353216u)) + uintBitsToFloat(0u);
        RVar[126u].x = _465;
        RVar[127u].y = _469;
        RVar[127u].z = _473;
        RVar[122u].x = _482;
        float _503 = (CBUFFER_1.values[5].z * ((-_465) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _508 = (CBUFFER_1.values[5].y * ((-_469) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        float _513 = (CBUFFER_1.values[5].x * ((-_473) + uintBitsToFloat(1065353216u))) + uintBitsToFloat(0u);
        RVar[123u].x = _503;
        RVar[123u].y = _508;
        RVar[123u].z = _513;
        RVar[2u].w = clamp(clamp(clamp(_460 + uintBitsToFloat(0u), 0.0, 1.0) + _482, 0.0, 1.0) + uintBitsToFloat(0u), 0.0, 1.0);
        float _525 = RVar[126u].x;
        float _528 = clamp((CBUFFER_1.values[4].z * _525) + _503, 0.0, 1.0);
        float _532 = RVar[127u].y;
        float _535 = clamp((CBUFFER_1.values[4].y * _532) + _508, 0.0, 1.0);
        float _539 = RVar[127u].z;
        float _542 = clamp((CBUFFER_1.values[4].x * _539) + _513, 0.0, 1.0);
        RVar[127u].y = _528;
        RVar[127u].z = _535;
        RVar[127u].w = _542;
        float _551 = RVar[0u].z;
        float _555 = RVar[0u].y;
        float _565 = RVar[0u].w;
        float _567 = RVar[127u].z;
        float _571 = RVar[0u].w;
        float _573 = RVar[127u].y;
        RVar[2u].x = ((RVar[0u].x + (-_542)) * RVar[0u].w) + RVar[127u].w;
        RVar[2u].y = ((_555 + (-_535)) * _565) + _567;
        RVar[2u].z = ((_551 + (-_528)) * _571) + _573;
        float _582 = RVar[7u].y;
        float _584 = RVar[7u].z;
        float _586 = RVar[7u].w;
        RVar[1u].x = RVar[7u].x;
        RVar[1u].y = _582;
        RVar[1u].z = _584;
        RVar[1u].w = _586;
        float _594 = RVar[2u].y;
        float _596 = RVar[2u].z;
        float _598 = RVar[2u].w;
        RVar[0u].x = RVar[2u].x;
        RVar[0u].y = _594;
        RVar[0u].z = _596;
        RVar[0u].w = _598;
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
    uint _674 = PS_PUSH.alphaFunc >> 8u;
    if (_674 == 1u)
    {
        _pixelTmp = vec4(1.0);
    }
    else
    {
        if (_674 == 2u)
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
    uint _702 = PS_PUSH.alphaFunc >> 8u;
    if (_702 == 1u)
    {
        _pixelTmp_1 = vec4(1.0);
    }
    else
    {
        if (_702 == 2u)
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